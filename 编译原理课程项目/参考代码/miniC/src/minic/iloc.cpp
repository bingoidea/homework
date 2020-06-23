#include "iloc.h"
#include "platform.h"
#include "symbol.h"
#include <sstream>

x86::x86(string op,string rs,string a1,string a2,string add)
	:opcode(op),result(rs),arg1(a1),arg2(a2),addition(add),dead(false)
{}

/*
	指令内容替换
*/
void x86::replace(string op,string rs,string a1,string a2,string add)
{
	opcode=op;
	result=rs;
	arg1=a1;
	arg2=a2;
	addition=add;
}

/*
	设置为无效指令
*/
void x86::setDead()
{
	dead=true;
}

/*
	输出函数
*/
string x86::outPut()
{
	if(dead)return "";
	if(opcode=="")return "";//占位指令
	string ret=opcode+" "+result;
	if(arg1!="")ret+=","+arg1;
	if(arg2!="")ret+=","+arg2;
	if(addition!="")ret+=","+addition;
	return ret;
}


#define emit(args...) code.push_back(new x86(args))

/*
		整数的字符串表达
		flag:是否在数字前添加#符号
*/
string ILoc::toStr(int num,int flag)
{
	string ret="";
	if(flag)ret="d";
	stringstream ss;
	ss<<num;
	ret=ss.str()+ret;//#123 =123
	return ret;
}

/*
	产生标签
*/
void ILoc::label(string name)
{
	emit(name,":");//.L1:
}

/*
	产生注释
*/
void ILoc::comment(string str)
{
	emit("#",str);//#hello world
}

/*
	0个操作数
*/
void ILoc::inst(string op)
{
    emit(op);
}
void ILoc::inst(string op,string rs)
{
	emit(op,rs);
}

/*
	一个操作数
*/
void ILoc::inst(string op,string rs,string arg1)
{
	emit(op,rs,arg1);
}

/*
	两个操作数
*/
void ILoc::inst(string op,string rs,string arg1,string arg2)
{
	emit(op,rs,arg1,arg2);
}

/*
	加载立即数 ldr r0,=#100
*/
void ILoc::ldr_imm(string rsReg,int num)
{
	if(Plat::constExpr(num))
		emit("mov",rsReg,toStr(num));//mov ax,#12
	else
		ldr_lb(rsReg,toStr(num,false));//ldr ax,=0xfff0
}

/*
	加载符号值 ldr r0,=g ldr r0,=.L1
*/
void ILoc::ldr_lb(string rsReg,string name)
{
	emit("mov",rsReg,name);//ldr ax,=.L1
}

/*
	基址寻址 ldr r0,[ebp,#100]
*/
void ILoc::ldr_base(string rsReg,string base,int diesp,bool isChar)
{
	if(Plat::isDisp(diesp)){//有效的偏移常量
		if(diesp)base="["+base+toStr(diesp)+"]";//[ebp,#-16] [ebp]

	}
	else{
		ldr_imm(rsReg,diesp);//ldr ax,=-4096
		base ="["+rsReg+"]"+"["+base+"]";//ebp,ax
	}
	//base="["+base+"]";//内存寻址
	emit("mov",rsReg,base);//ldr ax,[ebp,#-16] ldr ax,[ebp,ax]
}

/*
	基址寻址 str r0,[ebp,#100]
*/
void ILoc::str_base(string srcReg,string base,int diesp,string tmpReg,bool isChar)
{
	if(Plat::isDisp(diesp)){//有效的偏移常量
		if(diesp)base="["+base+toStr(diesp)+"]";//[ebp,#-16] [ebp]
		//if(diesp)base+=","+toStr(diesp);
	}
	else{
		ldr_imm(tmpReg,diesp);//ldr bx,=-4096
		base ="["+tmpReg+"]"+"["+base+"]";//ebp,bx
		//base+=","+tmpReg;
	}
	//base="["+base+"]";//内存寻址
	emit("mov",srcReg,base);//str ax,[ebp,#-16] str ax,[ebp,bx]
}

/*
	变量的初始化
*/
void ILoc::init_var(Var*var,string initReg,string tmpReg)
{
	if(!var->unInit()){//变量初始化了
		if(var->isBase())//基本类型初始化 100 'a'
			ldr_imm(initReg,var->getVal());//ldr ax,#100
		else//字符指针初始化
			ldr_lb(initReg,var->getPtrVal());//ldr ax,=.L1, .L1 byte "1234567"
		//初始值已经加载完成！一般在ax
		str_var(initReg,var,tmpReg);//将初始值保存到变量内存
	}
}

/*
	加载变量到寄存器，保证将变量放到reg中：ax/bx
*/
void ILoc::ldr_var(string rsReg,Var*var)
{
	if(!var)return;//无效变量
	bool isChar=var->isChar();//是否是字符变量，需要类型转换
	if(var->notConst()){//非常量
		int id=var->regId;//-1表示非寄存器，其他表示寄存器的索引值
		if(id!=-1)//寄存器变量
			emit("mov",rsReg,Plat::regName[id]);//mov ax,r2 | 这里有优化空间——消除ax
		else{//所有定义的变量和数组
			int off=var->getOffset();//栈帧偏移
			bool isGlb=!off;//变量偏移，0表示全局，其他表示局部
			bool isVar=!var->getArray();//纯变量，0表示数组，1表示变量
			if(isGlb){//全局符号
				ldr_lb(rsReg,var->getName());//ldr ax,=glb
				if(isVar)ldr_base(rsReg,rsReg,0,isChar);//ldr ax,[ax]
			}
			else{//局部符号
				if(isVar)ldr_base(rsReg,"ebp",off,isChar);//ldr ax,[ebp,#-16]
				else leaStack(rsReg,off);//add ax,ebp,#-16
			}
		}
	}
	else{//常量
		if(var->isBase())//是基本类型 100 'a'
			ldr_imm(rsReg,var->getVal());//ldr ax,#100
		else//常量字符串
			ldr_lb(rsReg,var->getName());//ldr ax,=.L1, .L1 byte "1234567"
	}
}

/*
	加载变量地址到寄存器
*/
void ILoc::lea_var(string rsReg,Var*var)
{
	//被加载的变量肯定不是常量！
	//被加载的变量肯定不是寄存器变量！
	int off=var->getOffset();//栈帧偏移
	bool isGlb=!off;//变量偏移，0表示全局，其他表示局部
	if(isGlb)//全局符号
		ldr_lb(rsReg,var->getName());//ldr bx,=glb 地址寄存器加载变量地址
	else{//局部符号
		leaStack(rsReg,off);//lea ax,[ebp,#-16]
	}
}

/*
	保存寄存器到变量，保证将计算结果（ax）保存到变量
*/
void ILoc::str_var(string srcReg,Var*var,string tmpReg)
{
	//被保存目标变量肯定不是常量！
	int id=var->regId;//-1表示非寄存器，其他表示寄存器的索引值
	bool isChar=var->isChar();//是否是字符变量，需要类型转换
	if(id!=-1){//寄存器变量
		emit("mov",Plat::regName[id],srcReg);//mov r2,ax | 这里有优化空间——消除ax
	}
	else{//所有定义的变量,不可能是数组！
		int off=var->getOffset();//栈帧偏移
		bool isGlb=!off;//变量偏移，0表示全局，其他表示局部
		if(isGlb){//全局符号
			ldr_lb(tmpReg,var->getName());//ldr bx,=glb 地址寄存器加载变量地址
			str_base(srcReg,tmpReg,0,tmpReg,isChar);//str ax,[bx]
		}
		else{//局部符号
			str_base(srcReg,"ebp",off,tmpReg,isChar);//str ax,[ebp,#-16]
		}
	}
	nop();//分割优化
}

/*
	加载栈内变量地址
*/
void ILoc::leaStack(string rsReg,int off)
{
	if(Plat::constExpr(off))
		emit("add",rsReg,"ebp",toStr(off));//add ax,ebp,#-16
	else{
		ldr_imm(rsReg,off);//ldr ax,=-257
		emit("add",rsReg,"ebp",rsReg);//add ax,ebp,ax
	}
}

/*
	分配栈帧
*/
void ILoc::allocStack(Fun*fun,string tmpReg)
{
	// int base=(fun->isRelocated())?(Plat::stackBase_protect):(Plat::stackBase);
	int base=Plat::stackBase;
	if(fun->isRelocated())base=Plat::stackBase_protect;
	int off=fun->getMaxDep()-base;//计算栈帧大小
	if(Plat::constExpr(off))
		emit("sub","esp","esp",toStr(off));//sub esp,esp,#16
	else{
		ldr_imm(tmpReg,off);//ldr ax,=257
		emit("sub","esp","esp",tmpReg);//sub esp,esp,ax
	}
}

/*
	加载函数的参数到寄存器
*/
void ILoc::ldr_args(Fun*fun)
{
	vector<Var*> args=fun->getParaVar();//获取参数
	for(unsigned int i=0;i<args.size();i++){
		Var*arg=args[i];
		if(arg->regId!=-1){//参数在寄存器，需要加载,不用理会是否是字符，统一4字节加载
			ldr_base(Plat::regName[arg->regId],"ebp",arg->getOffset(),false);//ldr r0,[ebp,#4]
		}
	}
}

/*
	调用库函数:rsReg=fun(arg1,arg2)
*/
void ILoc::call_lib(string fun,string rsReg,string reg1,string reg2)
{
	emit("push","ebp");//保护现场
	emit("mov","esp","ebp");
	emit("mov","ax",reg1);//传递操作数
	emit("mov","bx",reg2);
	emit("call",fun);
	emit("mov",rsReg,"ax");//取返回结果
	emit("mov","ebp","esp");//恢复现场
	emit("push","ebp");
	//emit("ldmfd","esp!","{r0-r7}");
}

/*
	调用函数fun
*/
void ILoc::call_fun(Fun*fun,string tmpReg)
{
	string funName=fun->getName();
	emit("call",funName);//函数返回值在ax,不需要保护
	int off=fun->getParaVar().size();//需要弹出参数的个数
	off*=4;//参数都是4字节
	if(Plat::constExpr(off))
		emit("add","esp","esp",toStr(off));//add esp,esp,#16
	else{
		ldr_imm(tmpReg,off);//ldr ax,=257
		emit("add","esp","esp",tmpReg);//add esp,esp,ax
	}
}

/*
	逻辑与
*/
void ILoc::logic_and(string rsReg,string reg1,string reg2)
{
	emit("cmp",reg1,"0d");//ax=0?
	emit("moveq",rsReg,"0d");//ax=0
	emit("movne",rsReg,"1d");//ax=1
	emit("cmpne",reg2,"0d");//bx=0?
	emit("moveq",rsReg,"0d");//ax=0
}

/*
	逻辑或
*/
void ILoc::logic_or(string rsReg,string reg1,string reg2)
{
	emit("cmp",reg1,"0d");//ax=0?
	emit("moveq",rsReg,"0d");//ax=0
	emit("movne",rsReg,"1d");//ax=1
	emit("cmpeq",reg2,"0d");//bx=0?
	emit("movne",rsReg,"1d");//ax=0
}

/*
	逻辑非
*/
void ILoc::logic_not(string rsReg,string reg1)
{
	emit("cmp",reg1,"0d");//ax=0
	emit("moveq",rsReg,"0d");//ax=1
	emit("movne",rsReg,"1d");//ax=0
}

/*
	比较
*/
void ILoc::cmp(string cmp,string cmpnot,string rsReg,string reg1,string reg2)
{
	emit("cmp",reg1,reg2);//ax ? bx
	emit("mov"+cmp,rsReg,"1d");//ax=0
	emit("mov"+cmpnot,rsReg,"0d");//ax=1
}

/*
	占位
*/
void ILoc::nop()
{
	emit("");//无操作符
}


ILoc::~ILoc()
{
	for(list<x86*>::iterator it=code.begin();it!=code.end();++it)
	{
		delete (*it);
	}
}

/*
	输出汇编
*/
void ILoc::outPut(FILE*file)
{
	for(list<x86*>::iterator it=code.begin();it!=code.end();++it)
	{
		string s=(*it)->outPut();
		if(s!="")fprintf(file,"\t%s\n",s.c_str());
	}
}

/*
	获取代码
*/
list<x86*>& ILoc::getCode()
{
	return code;
}
