#include "selector.h"
#include "intercode.h"
#include "symbol.h"
#include "platform.h"

Selector::Selector(vector<InterInst*>& irCode,ILoc& ilocCode)
	:ir(irCode),iloc(ilocCode)
{}

/*
	指令选择
*/
void Selector::select()
{
	for(unsigned int i=0;i<ir.size();i++){
		translate(ir[i]);
	}
}

/*
	翻译
*/
void Selector::translate(InterInst*inst)
{
	string label=inst->getLabel();
	if(label!=""){//标签打印
		iloc.label(label);
		return;
	}
	Operator op=inst->getOp();//操作符
	if(op==OP_ENTRY){//函数入口
		Fun*fun=inst->getFun();//函数
		//iloc.comment("函数入口");
		iloc.inst("push","ebp");
		iloc.inst("mov","ebp","esp");
		if(fun->isRelocated()){
			//iloc.inst("sub", "esp", "4d");
			iloc.inst("push","ax");
			iloc.inst("push","bx");
			iloc.inst("push","cx");
			iloc.inst("push","dx");
			iloc.inst("push","eip");//保护现场
			//iloc.inst("push","lr");
			//iloc.inst("push","pc");
			//iloc.inst("push","{ax-dx,ebp,ip,lr,pc}");
		}
		//else
			//iloc.inst("push","{ebp,ip,lr,pc}");//不用保护现场
		//iloc.inst("sub","ebp","ip","4d");
		//iloc.comment("开辟栈帧");
		iloc.allocStack(fun,"ax");//为fun分配栈帧
		//iloc.comment("加载参数变量到寄存器");
		iloc.ldr_args(fun);//加载参数到对应的寄存器
		//iloc.comment("函数内代码");
	}
	else if(op==OP_EXIT){//函数出口
		//iloc.comment("函数出口");
		if(inst->getFun()->isRelocated()){
            iloc.inst("pop","ax");
			iloc.inst("pop","bx");
			iloc.inst("pop","cx");
			iloc.inst("pop","dx");
			iloc.inst("pop","eip");
            iloc.inst("pop","ebp");//恢复现场
			iloc.inst("ret");
		}
		else
			iloc.inst("ret");//不用恢复现场
	}
	else if(op==OP_DEC){//处理声明的初始化
		iloc.init_var(inst->getArg1(),"ax","bx");//初始值在ax，可能用到bx
	}
	else if(op==OP_LEA){//取地址
		iloc.lea_var("ax",inst->getArg1());//&arg1 -> ax
		iloc.str_var("ax",inst->getResult(),"bx");//ax -> rs 可能用到bx
	}
	else if(op==OP_SET){//设置指针值
		iloc.ldr_var("ax",inst->getResult());//rs -> ax
		iloc.ldr_var("bx",inst->getArg1());//arg1 -> bx
		//虽然基址寄存器bx不能修改（bx又是临时寄存器），但是disp=0，因此不会使用bx作为临时寄存器
		iloc.str_base("ax","bx",0,"bx",inst->getArg1()->isCharPtr());//rs -> *arg1
		iloc.nop();//占位
	}
	else if(op==OP_JMP||op==OP_JT||op==OP_JF||op==OP_JNE||op==OP_RET||op==OP_RETV){//跳转,函数返回
		string des=inst->getTarget()->getLabel();//目标地址
		iloc.ldr_var("ax",inst->getArg1());//arg1 -> ax
		iloc.ldr_var("bx",inst->getArg2());//arg2 -> bx JNE需要
		switch(op){
			case OP_JMP:iloc.inst("jmp",des);break;
			case OP_JT:iloc.inst("cmp","ax","0d");iloc.inst("jnz",des);break;
			case OP_JF:iloc.inst("cmp","ax","0d");iloc.inst("jz",des);break;
			case OP_RET:iloc.inst("jmp",des);break;
			case OP_RETV:iloc.inst("jmp",des);break;
			case OP_JNE:
				iloc.cmp("ne","eq","ax","ax","bx");//ax!=bx -> ax
				iloc.inst("cmp","ax","0d");//ax!=0?
				iloc.inst("jnz",des);
				break;
		}
	}
	else if(op==OP_ARG){//参数入栈,直接push arg1 !
		iloc.ldr_var("ax",inst->getArg1());//arg1 -> ax
		iloc.inst("push","{ax}");//将ax压栈
		//iloc.str_base("ax","fp",inst->offset,"bx");//ax -> [fp,#offset]
	}
	else if(op==OP_CALL){//调用返回值函数
		iloc.call_fun(inst->getFun(),"bx");//fun() -> ax,恢复栈帧可能用到bx
		iloc.str_var("ax",inst->getResult(),"bx");//ax -> rs 可能用到bx
	}
	else if(op==OP_PROC){//调用无返回值函数
		iloc.call_fun(inst->getFun(),"bx");//fun()
	}
	else{//数值值表达式运算
		Var*rs=inst->getResult();
		Var*arg1=inst->getArg1();
		Var*arg2=inst->getArg2();
		iloc.ldr_var("ax",arg1);//arg1 -> ax
		iloc.ldr_var("bx",arg2);//arg2 -> bx
		switch(op)
		{
			//赋值
			case OP_AS:break;
			//算数
			case OP_ADD:iloc.inst("add","ax","ax","bx");break;
			case OP_SUB:iloc.inst("sub","ax","ax","bx");break;
			case OP_MUL:iloc.inst("mul","cx","ax","bx");iloc.inst("mov","ax","cx");break;
			case OP_DIV:iloc.call_lib("div","ax","ax","bx");break;
			case OP_MOD:iloc.call_lib("mod","ax","ax","bx");break;
			case OP_NEG:iloc.inst("mul","ax","#0","ax");break;//逆向减法ax=0-ax
			//比较
			case OP_GT:iloc.cmp("gt","le","ax","ax","bx");break;
			case OP_GE:iloc.cmp("ge","lt","ax","ax","bx");break;
			case OP_LT:iloc.cmp("lt","ge","ax","ax","bx");break;
			case OP_LE:iloc.cmp("le","gt","ax","ax","bx");break;
			case OP_EQU:iloc.cmp("eq","ne","ax","ax","bx");break;
			case OP_NE:iloc.cmp("ne","eq","ax","ax","bx");break;
			//逻辑
			case OP_AND:iloc.logic_and("ax","ax","bx");break;
			case OP_OR:iloc.logic_or("ax","ax","bx");break;
			case OP_NOT:iloc.logic_not("ax","ax");break;
			//指针,此处需要将类型转换考虑进去
			case OP_GET:iloc.ldr_base("ax","ax",0,rs->isChar());break;//a=*p
		}
		iloc.str_var("ax",rs,"bx");//ax -> rs 可能用到bx
	}
}
