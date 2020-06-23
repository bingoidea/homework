#include "iloc.h"
#include "platform.h"
#include "symbol.h"
#include <sstream>

x86::x86(string op,string rs,string a1,string a2,string add)
	:opcode(op),result(rs),arg1(a1),arg2(a2),addition(add),dead(false)
{}

/*
	ָ�������滻
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
	����Ϊ��Чָ��
*/
void x86::setDead()
{
	dead=true;
}

/*
	�������
*/
string x86::outPut()
{
	if(dead)return "";
	if(opcode=="")return "";//ռλָ��
	string ret=opcode+" "+result;
	if(arg1!="")ret+=","+arg1;
	if(arg2!="")ret+=","+arg2;
	if(addition!="")ret+=","+addition;
	return ret;
}


#define emit(args...) code.push_back(new x86(args))

/*
		�������ַ������
		flag:�Ƿ�������ǰ���#����
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
	������ǩ
*/
void ILoc::label(string name)
{
	emit(name,":");//.L1:
}

/*
	����ע��
*/
void ILoc::comment(string str)
{
	emit("#",str);//#hello world
}

/*
	0��������
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
	һ��������
*/
void ILoc::inst(string op,string rs,string arg1)
{
	emit(op,rs,arg1);
}

/*
	����������
*/
void ILoc::inst(string op,string rs,string arg1,string arg2)
{
	emit(op,rs,arg1,arg2);
}

/*
	���������� ldr r0,=#100
*/
void ILoc::ldr_imm(string rsReg,int num)
{
	if(Plat::constExpr(num))
		emit("mov",rsReg,toStr(num));//mov ax,#12
	else
		ldr_lb(rsReg,toStr(num,false));//ldr ax,=0xfff0
}

/*
	���ط���ֵ ldr r0,=g ldr r0,=.L1
*/
void ILoc::ldr_lb(string rsReg,string name)
{
	emit("mov",rsReg,name);//ldr ax,=.L1
}

/*
	��ַѰַ ldr r0,[ebp,#100]
*/
void ILoc::ldr_base(string rsReg,string base,int diesp,bool isChar)
{
	if(Plat::isDisp(diesp)){//��Ч��ƫ�Ƴ���
		if(diesp)base="["+base+toStr(diesp)+"]";//[ebp,#-16] [ebp]

	}
	else{
		ldr_imm(rsReg,diesp);//ldr ax,=-4096
		base ="["+rsReg+"]"+"["+base+"]";//ebp,ax
	}
	//base="["+base+"]";//�ڴ�Ѱַ
	emit("mov",rsReg,base);//ldr ax,[ebp,#-16] ldr ax,[ebp,ax]
}

/*
	��ַѰַ str r0,[ebp,#100]
*/
void ILoc::str_base(string srcReg,string base,int diesp,string tmpReg,bool isChar)
{
	if(Plat::isDisp(diesp)){//��Ч��ƫ�Ƴ���
		if(diesp)base="["+base+toStr(diesp)+"]";//[ebp,#-16] [ebp]
		//if(diesp)base+=","+toStr(diesp);
	}
	else{
		ldr_imm(tmpReg,diesp);//ldr bx,=-4096
		base ="["+tmpReg+"]"+"["+base+"]";//ebp,bx
		//base+=","+tmpReg;
	}
	//base="["+base+"]";//�ڴ�Ѱַ
	emit("mov",srcReg,base);//str ax,[ebp,#-16] str ax,[ebp,bx]
}

/*
	�����ĳ�ʼ��
*/
void ILoc::init_var(Var*var,string initReg,string tmpReg)
{
	if(!var->unInit()){//������ʼ����
		if(var->isBase())//�������ͳ�ʼ�� 100 'a'
			ldr_imm(initReg,var->getVal());//ldr ax,#100
		else//�ַ�ָ���ʼ��
			ldr_lb(initReg,var->getPtrVal());//ldr ax,=.L1, .L1 byte "1234567"
		//��ʼֵ�Ѿ�������ɣ�һ����ax
		str_var(initReg,var,tmpReg);//����ʼֵ���浽�����ڴ�
	}
}

/*
	���ر������Ĵ�������֤�������ŵ�reg�У�ax/bx
*/
void ILoc::ldr_var(string rsReg,Var*var)
{
	if(!var)return;//��Ч����
	bool isChar=var->isChar();//�Ƿ����ַ���������Ҫ����ת��
	if(var->notConst()){//�ǳ���
		int id=var->regId;//-1��ʾ�ǼĴ�����������ʾ�Ĵ���������ֵ
		if(id!=-1)//�Ĵ�������
			emit("mov",rsReg,Plat::regName[id]);//mov ax,r2 | �������Ż��ռ䡪������ax
		else{//���ж���ı���������
			int off=var->getOffset();//ջ֡ƫ��
			bool isGlb=!off;//����ƫ�ƣ�0��ʾȫ�֣�������ʾ�ֲ�
			bool isVar=!var->getArray();//��������0��ʾ���飬1��ʾ����
			if(isGlb){//ȫ�ַ���
				ldr_lb(rsReg,var->getName());//ldr ax,=glb
				if(isVar)ldr_base(rsReg,rsReg,0,isChar);//ldr ax,[ax]
			}
			else{//�ֲ�����
				if(isVar)ldr_base(rsReg,"ebp",off,isChar);//ldr ax,[ebp,#-16]
				else leaStack(rsReg,off);//add ax,ebp,#-16
			}
		}
	}
	else{//����
		if(var->isBase())//�ǻ������� 100 'a'
			ldr_imm(rsReg,var->getVal());//ldr ax,#100
		else//�����ַ���
			ldr_lb(rsReg,var->getName());//ldr ax,=.L1, .L1 byte "1234567"
	}
}

/*
	���ر�����ַ���Ĵ���
*/
void ILoc::lea_var(string rsReg,Var*var)
{
	//�����صı����϶����ǳ�����
	//�����صı����϶����ǼĴ���������
	int off=var->getOffset();//ջ֡ƫ��
	bool isGlb=!off;//����ƫ�ƣ�0��ʾȫ�֣�������ʾ�ֲ�
	if(isGlb)//ȫ�ַ���
		ldr_lb(rsReg,var->getName());//ldr bx,=glb ��ַ�Ĵ������ر�����ַ
	else{//�ֲ�����
		leaStack(rsReg,off);//lea ax,[ebp,#-16]
	}
}

/*
	����Ĵ�������������֤����������ax�����浽����
*/
void ILoc::str_var(string srcReg,Var*var,string tmpReg)
{
	//������Ŀ������϶����ǳ�����
	int id=var->regId;//-1��ʾ�ǼĴ�����������ʾ�Ĵ���������ֵ
	bool isChar=var->isChar();//�Ƿ����ַ���������Ҫ����ת��
	if(id!=-1){//�Ĵ�������
		emit("mov",Plat::regName[id],srcReg);//mov r2,ax | �������Ż��ռ䡪������ax
	}
	else{//���ж���ı���,�����������飡
		int off=var->getOffset();//ջ֡ƫ��
		bool isGlb=!off;//����ƫ�ƣ�0��ʾȫ�֣�������ʾ�ֲ�
		if(isGlb){//ȫ�ַ���
			ldr_lb(tmpReg,var->getName());//ldr bx,=glb ��ַ�Ĵ������ر�����ַ
			str_base(srcReg,tmpReg,0,tmpReg,isChar);//str ax,[bx]
		}
		else{//�ֲ�����
			str_base(srcReg,"ebp",off,tmpReg,isChar);//str ax,[ebp,#-16]
		}
	}
	nop();//�ָ��Ż�
}

/*
	����ջ�ڱ�����ַ
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
	����ջ֡
*/
void ILoc::allocStack(Fun*fun,string tmpReg)
{
	// int base=(fun->isRelocated())?(Plat::stackBase_protect):(Plat::stackBase);
	int base=Plat::stackBase;
	if(fun->isRelocated())base=Plat::stackBase_protect;
	int off=fun->getMaxDep()-base;//����ջ֡��С
	if(Plat::constExpr(off))
		emit("sub","esp","esp",toStr(off));//sub esp,esp,#16
	else{
		ldr_imm(tmpReg,off);//ldr ax,=257
		emit("sub","esp","esp",tmpReg);//sub esp,esp,ax
	}
}

/*
	���غ����Ĳ������Ĵ���
*/
void ILoc::ldr_args(Fun*fun)
{
	vector<Var*> args=fun->getParaVar();//��ȡ����
	for(unsigned int i=0;i<args.size();i++){
		Var*arg=args[i];
		if(arg->regId!=-1){//�����ڼĴ�������Ҫ����,��������Ƿ����ַ���ͳһ4�ֽڼ���
			ldr_base(Plat::regName[arg->regId],"ebp",arg->getOffset(),false);//ldr r0,[ebp,#4]
		}
	}
}

/*
	���ÿ⺯��:rsReg=fun(arg1,arg2)
*/
void ILoc::call_lib(string fun,string rsReg,string reg1,string reg2)
{
	emit("push","ebp");//�����ֳ�
	emit("mov","esp","ebp");
	emit("mov","ax",reg1);//���ݲ�����
	emit("mov","bx",reg2);
	emit("call",fun);
	emit("mov",rsReg,"ax");//ȡ���ؽ��
	emit("mov","ebp","esp");//�ָ��ֳ�
	emit("push","ebp");
	//emit("ldmfd","esp!","{r0-r7}");
}

/*
	���ú���fun
*/
void ILoc::call_fun(Fun*fun,string tmpReg)
{
	string funName=fun->getName();
	emit("call",funName);//��������ֵ��ax,����Ҫ����
	int off=fun->getParaVar().size();//��Ҫ���������ĸ���
	off*=4;//��������4�ֽ�
	if(Plat::constExpr(off))
		emit("add","esp","esp",toStr(off));//add esp,esp,#16
	else{
		ldr_imm(tmpReg,off);//ldr ax,=257
		emit("add","esp","esp",tmpReg);//add esp,esp,ax
	}
}

/*
	�߼���
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
	�߼���
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
	�߼���
*/
void ILoc::logic_not(string rsReg,string reg1)
{
	emit("cmp",reg1,"0d");//ax=0
	emit("moveq",rsReg,"0d");//ax=1
	emit("movne",rsReg,"1d");//ax=0
}

/*
	�Ƚ�
*/
void ILoc::cmp(string cmp,string cmpnot,string rsReg,string reg1,string reg2)
{
	emit("cmp",reg1,reg2);//ax ? bx
	emit("mov"+cmp,rsReg,"1d");//ax=0
	emit("mov"+cmpnot,rsReg,"0d");//ax=1
}

/*
	ռλ
*/
void ILoc::nop()
{
	emit("");//�޲�����
}


ILoc::~ILoc()
{
	for(list<x86*>::iterator it=code.begin();it!=code.end();++it)
	{
		delete (*it);
	}
}

/*
	������
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
	��ȡ����
*/
list<x86*>& ILoc::getCode()
{
	return code;
}
