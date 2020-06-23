#include "selector.h"
#include "intercode.h"
#include "symbol.h"
#include "platform.h"

Selector::Selector(vector<InterInst*>& irCode,ILoc& ilocCode)
	:ir(irCode),iloc(ilocCode)
{}

/*
	ָ��ѡ��
*/
void Selector::select()
{
	for(unsigned int i=0;i<ir.size();i++){
		translate(ir[i]);
	}
}

/*
	����
*/
void Selector::translate(InterInst*inst)
{
	string label=inst->getLabel();
	if(label!=""){//��ǩ��ӡ
		iloc.label(label);
		return;
	}
	Operator op=inst->getOp();//������
	if(op==OP_ENTRY){//�������
		Fun*fun=inst->getFun();//����
		//iloc.comment("�������");
		iloc.inst("push","ebp");
		iloc.inst("mov","ebp","esp");
		if(fun->isRelocated()){
			//iloc.inst("sub", "esp", "4d");
			iloc.inst("push","ax");
			iloc.inst("push","bx");
			iloc.inst("push","cx");
			iloc.inst("push","dx");
			iloc.inst("push","eip");//�����ֳ�
			//iloc.inst("push","lr");
			//iloc.inst("push","pc");
			//iloc.inst("push","{ax-dx,ebp,ip,lr,pc}");
		}
		//else
			//iloc.inst("push","{ebp,ip,lr,pc}");//���ñ����ֳ�
		//iloc.inst("sub","ebp","ip","4d");
		//iloc.comment("����ջ֡");
		iloc.allocStack(fun,"ax");//Ϊfun����ջ֡
		//iloc.comment("���ز����������Ĵ���");
		iloc.ldr_args(fun);//���ز�������Ӧ�ļĴ���
		//iloc.comment("�����ڴ���");
	}
	else if(op==OP_EXIT){//��������
		//iloc.comment("��������");
		if(inst->getFun()->isRelocated()){
            iloc.inst("pop","ax");
			iloc.inst("pop","bx");
			iloc.inst("pop","cx");
			iloc.inst("pop","dx");
			iloc.inst("pop","eip");
            iloc.inst("pop","ebp");//�ָ��ֳ�
			iloc.inst("ret");
		}
		else
			iloc.inst("ret");//���ûָ��ֳ�
	}
	else if(op==OP_DEC){//���������ĳ�ʼ��
		iloc.init_var(inst->getArg1(),"ax","bx");//��ʼֵ��ax�������õ�bx
	}
	else if(op==OP_LEA){//ȡ��ַ
		iloc.lea_var("ax",inst->getArg1());//&arg1 -> ax
		iloc.str_var("ax",inst->getResult(),"bx");//ax -> rs �����õ�bx
	}
	else if(op==OP_SET){//����ָ��ֵ
		iloc.ldr_var("ax",inst->getResult());//rs -> ax
		iloc.ldr_var("bx",inst->getArg1());//arg1 -> bx
		//��Ȼ��ַ�Ĵ���bx�����޸ģ�bx������ʱ�Ĵ�����������disp=0����˲���ʹ��bx��Ϊ��ʱ�Ĵ���
		iloc.str_base("ax","bx",0,"bx",inst->getArg1()->isCharPtr());//rs -> *arg1
		iloc.nop();//ռλ
	}
	else if(op==OP_JMP||op==OP_JT||op==OP_JF||op==OP_JNE||op==OP_RET||op==OP_RETV){//��ת,��������
		string des=inst->getTarget()->getLabel();//Ŀ���ַ
		iloc.ldr_var("ax",inst->getArg1());//arg1 -> ax
		iloc.ldr_var("bx",inst->getArg2());//arg2 -> bx JNE��Ҫ
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
	else if(op==OP_ARG){//������ջ,ֱ��push arg1 !
		iloc.ldr_var("ax",inst->getArg1());//arg1 -> ax
		iloc.inst("push","{ax}");//��axѹջ
		//iloc.str_base("ax","fp",inst->offset,"bx");//ax -> [fp,#offset]
	}
	else if(op==OP_CALL){//���÷���ֵ����
		iloc.call_fun(inst->getFun(),"bx");//fun() -> ax,�ָ�ջ֡�����õ�bx
		iloc.str_var("ax",inst->getResult(),"bx");//ax -> rs �����õ�bx
	}
	else if(op==OP_PROC){//�����޷���ֵ����
		iloc.call_fun(inst->getFun(),"bx");//fun()
	}
	else{//��ֵֵ���ʽ����
		Var*rs=inst->getResult();
		Var*arg1=inst->getArg1();
		Var*arg2=inst->getArg2();
		iloc.ldr_var("ax",arg1);//arg1 -> ax
		iloc.ldr_var("bx",arg2);//arg2 -> bx
		switch(op)
		{
			//��ֵ
			case OP_AS:break;
			//����
			case OP_ADD:iloc.inst("add","ax","ax","bx");break;
			case OP_SUB:iloc.inst("sub","ax","ax","bx");break;
			case OP_MUL:iloc.inst("mul","cx","ax","bx");iloc.inst("mov","ax","cx");break;
			case OP_DIV:iloc.call_lib("div","ax","ax","bx");break;
			case OP_MOD:iloc.call_lib("mod","ax","ax","bx");break;
			case OP_NEG:iloc.inst("mul","ax","#0","ax");break;//�������ax=0-ax
			//�Ƚ�
			case OP_GT:iloc.cmp("gt","le","ax","ax","bx");break;
			case OP_GE:iloc.cmp("ge","lt","ax","ax","bx");break;
			case OP_LT:iloc.cmp("lt","ge","ax","ax","bx");break;
			case OP_LE:iloc.cmp("le","gt","ax","ax","bx");break;
			case OP_EQU:iloc.cmp("eq","ne","ax","ax","bx");break;
			case OP_NE:iloc.cmp("ne","eq","ax","ax","bx");break;
			//�߼�
			case OP_AND:iloc.logic_and("ax","ax","bx");break;
			case OP_OR:iloc.logic_or("ax","ax","bx");break;
			case OP_NOT:iloc.logic_not("ax","ax");break;
			//ָ��,�˴���Ҫ������ת�����ǽ�ȥ
			case OP_GET:iloc.ldr_base("ax","ax",0,rs->isChar());break;//a=*p
		}
		iloc.str_var("ax",rs,"bx");//ax -> rs �����õ�bx
	}
}
