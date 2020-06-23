#include "symbol.h"
#include "error.h"
#include "token.h"
#include "genir.h"
#include "symtab.h"
#include "compiler.h"
#include "dfg.h"
#include "redundelim.h"
#include "livevar.h"
#include "alloc.h"
#include "selector.h"
#include "platform.h"


//��ӡ�������
#define SEMERROR(code,name) Error::semError(code,name)

/*******************************************************************************
                                   �����ṹ
*******************************************************************************/

/*
	��ȡVOID�������
*/
Var* Var::getVoid()
{
	return SymTab::voidVar;
}

/*
	void����
*/
Var::Var()
{
	clear();
	setName("<void>");//�����������
	setLeft(false);
	intVal=0;//��¼������ֵ
	literal=false;//������������־
	type=KW_VOID;//hack����
	isPtr=true;//�����������ͱ�־
}


/*
	��ȡtrue����
*/
Var* Var::getTrue()
{
	return SymTab::one;
}

/*
	��ȡ��������
*/
Var* Var::getStep(Var*v)
{
	if(v->isBase())return SymTab::one;
	else if(v->type==KW_CHAR)return SymTab::one;
	else if(v->type==KW_INT)return SymTab::four;
	else return NULL;
}

/*
	�ؼ���Ϣ��ʼ��
*/
void Var::clear()
{
	scopePath.push_back(-1);//Ĭ��ȫ��������
	externed=false;
	isPtr=false;
	isArray=false;
	isLeft=true;//Ĭ�ϱ����ǿ�����Ϊ��ֵ��
	inited=false;
	literal=false;
	size=0;
	offset=0;
	ptr=NULL;//û��ָ��ǰ������ָ�����
	index=-1;//��Ч����
	initData=NULL;
	live=false;
	regId=-1;//Ĭ�Ϸ����ڴ�
	inMem=false;
}

/*
	��ʱ����
*/
Var::Var(vector<int>&sp,Tag t,bool ptr)
{
	clear();
	scopePath=sp;//��ʼ��·��
	setType(t);
	setPtr(ptr);
	setName("");
	setLeft(false);
}

/*
	������һ����ʱ����
*/
Var::Var(vector<int>&sp,Var*v)
{
	clear();
	scopePath=sp;//��ʼ��·��
	setType(v->type);
	setPtr(v->isPtr||v->isArray);//���� ָ�붼��ָ��
	setName("");//�½�����
	setLeft(false);
}

/*
	������ָ��
*/
Var::Var(vector<int>&sp,bool ext,Tag t,bool ptr,string name,Var*init)
{
	clear();
	scopePath=sp;//��ʼ��·��
	setExtern(ext);
	setType(t);
	setPtr(ptr);
	setName(name);
	initData=init;
}

/*
	����
*/
Var::Var(vector<int>&sp,bool ext,Tag t,string name,int len)
{
	clear();
	scopePath=sp;//��ʼ��·��
	setExtern(ext);
	setType(t);
	setName(name);
	setArray(len);
}

/*
	��������
*/
Var::Var(int val)
{
	clear();
	setName("<int>");//�����������
	literal=true;
	setLeft(false);
	setType(KW_INT);
	intVal=val;//��¼������ֵ
}


/*
	����,���漰������ı仯���ַ����洢���ַ���������������Ϊ��ʼֵ(ʹ����ɾ��)
*/
Var::Var(Token*lt)
{
	clear();
	literal=true;
	setLeft(false);
	switch(lt->tag){
		case NUM:
			setType(KW_INT);
			name="<int>";//������Ϊ����
			intVal=((Num*)lt)->val;//��¼������ֵ
			break;
		case CH:
			setType(KW_CHAR);
			name="<char>";//������Ϊ����
			intVal=0;//��λ��0
			charVal=((Char*)lt)->ch;//��¼�ַ�ֵ
			break;
		case STR:
			setType(KW_CHAR);
			name=GenIR::genLb();//����һ���µ�����
			strVal=((Str*)lt)->str;//��¼�ַ���ֵ
			setArray(strVal.size()+1);//�ַ�����Ϊ�ַ�����洢
			break;
        default : break;
	}
}

/*
	����extern
*/
void Var::setExtern(bool ext)
{
	externed=ext;
	size=0;
}

/*
	��������
*/
void Var::setType(Tag t)
{
	type=t;
	if(type==KW_VOID){//��void����
		SEMERROR(VOID_VAR,"");//������ʹ��void����
		type=KW_INT;//Ĭ��Ϊint
	}
	if(!externed&&type==KW_INT)size=4;//����4�ֽ�
	else if(!externed&&type==KW_CHAR)size=1;//�ַ�1�ֽ�
}

/*
	����ָ��
*/
void Var::setPtr(bool ptr)
{
	if(!ptr)return;
	isPtr=true;
	if(!externed)size=4;//ָ�붼��4�ֽ�
}

/*
	��������
*/
void Var::setName(string n)
{
	if(n=="")
		n=GenIR::genLb();
	name=n;
}

/*
	��������
*/
void Var::setArray(int len)
{
	if(len<=0){
		SEMERROR(ARRAY_LEN_INVALID,name);//���鳤��С�ڵ���0����
		return ;
	}
	else{
		isArray=true;
		isLeft=false;//���鲻����Ϊ��ֵ
		arraySize=len;
		if(!externed)size*=len;//������С�������鳤��
	}
}

/*
	��ʼ���������Ϣ��¼�����鲻�����ʼ��
	�ֲ�������ʼ�����ʹ���м��������������true
*/
bool Var::setInit()
{
	Var*init=initData;//ȡ����ֵ����
	if(!init)return false;//û�г�ʼ�����ʽ
	inited=false;//Ĭ�ϳ�ʼ��ʧ��
	if(externed)
		SEMERROR(DEC_INIT_DENY,name);//�����������ʼ��
	else if(!GenIR::typeCheck(this,init))
		SEMERROR(VAR_INIT_ERR,name);//���ͼ�鲻����
	else if(init->literal){//ʹ�ó�����ʼ��
		inited=true;//��ʼ���ɹ���
		if(init->isArray)//��ʼ�����������飬�����ַ���
			ptrVal=init->name;//�ַ�ָ�������ʼֵ=�����ַ���������
		else//��������
			intVal=init->intVal;//������ֵ����
	}
	else{//��ʼֵ���ǳ���
		if(scopePath.size()==1)//����ʼ��������ȫ�ֱ���
			SEMERROR(GLB_INIT_ERR,name);//ȫ�ֱ�����ʼ�������ǳ���
		else//����ʼ�������Ǿֲ�����
			return true;
	}
	// if(init->literal && !(init->isArray))//ɾ���������ַ���ʼ������
	// 	delete init;//�����ʱ������������ַ�������ʱ������������Ѿ��ڷ��ű��ڣ�
	return false;
}

/*
	��ȡ��ʼ����������
*/
Var* Var::getInitData()
{
	return initData;
}


/*
	��ȡextern
*/
bool Var::getExtern()
{
	return externed;
}

/*
	��ȡ������·��
*/
vector<int>& Var::getPath()
{
	return scopePath;
}

/*
	��ȡ����
*/
Tag Var::getType()
{
	return type;
}

/*
	�ж��Ƿ����ַ�����
*/
bool Var::isChar()
{
	return (type==KW_CHAR) && isBase();//�ǻ������ַ�����
}

/*
	�ж��ַ�ָ��
*/
bool Var::isCharPtr()
{
	return (type==KW_CHAR) && !isBase();//�ַ�ָ������ַ�����
}

/*
	��ȡָ��
*/
bool Var::getPtr()
{
	return isPtr;
}

/*
	��ȡ����
*/
string Var::getName()
{
	return name;
}

/*
	��ȡ����
*/
bool Var::getArray()
{
	return isArray;
}

/*
	����ָ�����
*/
void Var::setPointer(Var* p)
{
	ptr=p;
}

/*
	��ȡָ�����
*/
Var* Var::getPointer()
{
	return ptr;
}

/*
	��ȡ�ַ�ָ������
*/
string Var::getPtrVal()
{
	return ptrVal;
}

/*
	��ȡ�ַ�����������
*/
string Var::getStrVal()
{
	return strVal;
}

/*
	��ȡ�ַ�������ԭʼ���ݣ��������ַ�ת��
*/
string Var::getRawStr()
{
	string raw;
	for(int i=0;i<strVal.size();i++){
		switch(strVal[i])
		{
			case '\n':raw.append("\\n");break;
			case '\t':raw.append("\\t");break;
			case '\0':raw.append("\\000");break;
			case '\\':raw.append("\\\\");break;
			case '\"':raw.append("\\\"");break;
			default:raw.push_back(strVal[i]);
		}
	}
	raw.append("\\000");//�������
	return raw;
}

/*
	���ñ�������ֵ
*/
void Var::setLeft(bool lf)
{
	isLeft=lf;
}

/*
	��ȡ��������ֵ
*/
bool Var::getLeft()
{
	return isLeft;
}

/*
	����ջ֡ƫ��
*/
void Var::setOffset(int off)
{
	offset=off;
}

/*
	��ȡջ֡ƫ��
*/
int Var::getOffset()
{
	return offset;
}


/*
	��ȡ������С
*/
int Var::getSize()
{
	return size;
}

/*
	������
*/
bool Var::isVoid()
{
	return type==KW_VOID;
}

/*
	�ǻ�������
*/
bool Var::isBase()
{
	return !isArray && !isPtr;
}

/*
	����������
*/
bool Var::isRef()
{
	return !!ptr;
}

/*
	�Ƿ��ʼ��
*/
bool Var::unInit()
{
	return !inited;
}

/*
	�Ƿ��ǳ���
*/
bool Var::notConst()
{
	return !literal;
}

/*
	��ȡ����ֵ
*/
int Var::getVal()
{
	return intVal;
}

/*
		�ǻ������ͳ������ַ������⣩��û�д洢�ڷ��ű���Ҫ�����ڴ����
*/
bool Var::isLiteral()
{
	return this->literal&&isBase();
}



/*
	����������м������ʽ
*/
void Var::value()
{
	if(literal){//��������
		if(type==KW_INT)
			printf("%d",intVal);
		else if(type==KW_CHAR){
			if(isArray)
				printf("%s",name.c_str());
			else
				printf("%d",charVal);
		}
	}
	else
		printf("%s",name.c_str());
}

/*
	���������Ϣ
*/
void Var::toString()
{
	if(externed)printf("externed ");
	//���type
	printf("%s",tokenName[type]);
	//���ָ��
	if(isPtr)printf("*");
	//�������
	printf(" %s",name.c_str());
	//�������
	if(isArray)printf("[%d]",arraySize);
	//�����ʼֵ
	if(inited){
		printf(" = ");
		switch(type){
			case KW_INT:printf("%d",intVal);break;
			case KW_CHAR:
				if(isPtr)printf("<%s>",ptrVal.c_str());
				else printf("%c",charVal);
				break;
            default: break;
		}
	}
	printf("; size=%d scope=\"",size);
	for(int i=0;i<scopePath.size();i++){
		printf("/%d",scopePath[i]);
	}
	printf("\" ");
	if(offset>0)
		printf("addr=[ebp+%d]",offset);
	else if(offset<0)
		printf("addr=[ebp%d]",offset);
	else if(name[0]!='<')
		printf("addr=<%s>",name.c_str());
	else
		printf("value='%d'",getVal());
}

/*******************************************************************************
                                   �����ṹ
*******************************************************************************/
/*
	���캯������������ֵ+����+�����б�
*/
Fun::Fun(bool ext,Tag t,string n,vector<Var*>&paraList)
{
	externed=ext;
	type=t;
	name=n;
	paraVar=paraList;
	curEsp=Plat::stackBase;//û��ִ�мĴ�������ǰ������Ҫ�����ֳ���ջ֡��ַ����Ҫ������
	maxDepth=Plat::stackBase;//��ֹû�ж���ֲ������������ֵ����
	//�����ֳ��ͻָ��ֳ��к����ڲ��������˲���ƫ�Ʋ���Ҫ������
	for(int i=0,argOff=4;i<paraVar.size();i++,argOff+=4){//��ʼ������������ַ�����ң�������ջ���ҵ���
		paraVar[i]->setOffset(argOff);
	}
	dfg=NULL;
	relocated=false;
}

Fun::~Fun()
{
	if(dfg)delete dfg;//����������ͼ
}


/*
	��λ�ֲ�����ջ֡ƫ��
*/
void Fun::locate(Var*var)
{
	int size=var->getSize();
	size+=(4-size%4)%4;//����4�ֽڵĴ�С����������ֲ�����
	scopeEsp.back()+=size;//�ۼ��������С
	curEsp+=size;//�ۼƵ�ǰ�������С
	var->setOffset(-curEsp);//�ֲ�����ƫ��Ϊ����
}

/*
	��������ƥ��
*/
#define SEMWARN(code,name) Error::semWarn(code,name)
bool Fun::match(Fun*f)
{
	//���ֺ����ķ���ֵ
	if(name!=f->name)
		return false;
	if(paraVar.size()!=f->paraVar.size())
		return false;
	int len=paraVar.size();
	for(int i=0;i<len;i++){
		if(GenIR::typeCheck(paraVar[i],f->paraVar[i])){//���ͼ���
			if(paraVar[i]->getType()!=f->paraVar[i]->getType()){//���ǲ���ȫƥ��
				SEMWARN(FUN_DEC_CONFLICT,name);//����������ͻ��������
			}
		}
		else
			return false;
	}
	//ƥ��ɹ�������֤��������
	if(type!=f->type){
		SEMWARN(FUN_RET_CONFLICT,name);//��������ֵ��ͻ��������
	}
	return true;
}

/*
	�в�ʵ��ƥ��
*/
bool Fun::match(vector<Var*>&args)
{
	if(paraVar.size()!=args.size())
		return false;
	int len=paraVar.size();
	for(int i=0;i<len;i++){
		if(!GenIR::typeCheck(paraVar[i],args[i]))//���ͼ�鲻����
			return false;
	}
	return true;
}

/*
	����������ת��Ϊ���壬��Ҫ���������б��趨extern
*/
void Fun::define(Fun*def)
{
	externed=false;//����
	paraVar=def->paraVar;//��������
}

/*
	���һ���м����
*/
void Fun::addInst(InterInst*inst)
{
	interCode.addInst(inst);
}

/*
	���ú������ص�
*/
void Fun::setReturnPoint(InterInst*inst)
{
	returnPoint=inst;
}

/*
	��ȡ�������ص�
*/
InterInst* Fun::getReturnPoint()
{
	return returnPoint;
}

/*
	����һ���µ�������
*/
void Fun::enterScope()
{
	scopeEsp.push_back(0);
}

/*
	�뿪��ǰ������
*/
void Fun::leaveScope()
{
	maxDepth=(curEsp>maxDepth)?curEsp:maxDepth;//����������
	curEsp-=scopeEsp.back();
	scopeEsp.pop_back();
}

/*
	����extern
*/
void Fun::setExtern(bool ext)
{
	externed=ext;
}

/*
	��ȡextern
*/
bool Fun::getExtern()
{
	return externed;
}

Tag Fun::getType()
{
	return type;
}

/*
	��ȡ����
*/
string& Fun::getName()
{
	return name;
}

/*
	��ȡ�����б�����Ϊ�������ɼ��ش���
*/
vector<Var*>& Fun::getParaVar()
{
	return paraVar;
}


/*
	�����Ϣ
*/
void Fun::toString()
{
	//���type
	printf("%s",tokenName[type]);
	//�������
	printf(" %s",name.c_str());
	//��������б�
	printf("(");
	for(int i=0;i<paraVar.size();i++){
		printf("<%s>",paraVar[i]->getName().c_str());
		if(i!=paraVar.size()-1)printf(",");
	}
	printf(")");
	if(externed)printf(";\n");
	else{
		printf(":\n");
		printf("\t\tmaxDepth=%d\n",maxDepth);
	}
}

/*
	ִ���Ż�����
*/
/*void Fun::optimize(SymTab*tab)
{
	if(externed)return;//��������������
	//������ͼ
	dfg=new DFG(interCode);//����������ͼ
	//if(Args::showBlock)dfg->toString();//������������ͼ��ϵ
	if(!Args::opt)return;//��ִ���Ż�

	//������������������������ת�Ż������ɴ��������
	ConstPropagation conPro(dfg,tab,paraVar);//��������
#ifdef CONST
	conPro.propagate();//��������
#endif

	//��������
	RedundElim re(dfg,tab);
#ifdef RED
	re.elimate();
#endif

	//��д����
	CopyPropagation cp(dfg);
#ifdef DEAD
	cp.propagate();
#endif

	//��Ծ����
	LiveVar lv(dfg,tab,paraVar);
#ifdef DEAD
	lv.elimateDeadCode();
#else
	#ifdef REG
		lv.analyse();
	#endif
#endif

	//�Ż�����洢��optCode
	dfg->toCode(optCode);//����������ͼΪ�м����

	//�Ĵ�������;ֲ�����ջ��ַ���¼���
	CoGraph cg(optCode,paraVar,&lv,this);//��ʼ����ͻͼ
	cg.alloc();//���·�������ļĴ�����ջ֡��ַ
}
*/
/*
	����м����
*/
void Fun::printInterCode()
{
	if(externed)return;
	printf("-------------<%s>Start--------------\n",name.c_str());
	interCode.toString();
	printf("--------------<%s>End---------------\n",name.c_str());
}

/*
	����Ż�����м����
*/
/*void Fun::printOptCode()
{
	if(externed)return;
	printf("-------------<%s>Start--------------\n",name.c_str());
	for (list<InterInst*>::iterator i = optCode.begin(); i != optCode.end(); ++i)
	{
		(*i)->toString();
	}
	printf("--------------<%s>End---------------\n",name.c_str());
}
*/


/*
	���������
*/
void Fun::genAsm(FILE*file)
{
	if(externed)return;
	//�������յĴ���,����Ż������Ż�����м���룬���������ͨ���м����
	vector<InterInst*> code;
	/*if(Args::opt){//�����Ż�
		for(list<InterInst*>::iterator it=optCode.begin();it!=optCode.end();++it){
			code.push_back(*it);
		}
	}
	else{//δ�Ż������м���뵼��*/
		code=interCode.getCode();
	//}
	const char* pname=name.c_str();
	fprintf(file,"#����%s����\n",pname);
	fprintf(file,"\t.global %s\n",pname);//.global fun\n
	fprintf(file,"%s:\n",pname);//fun:\n
	ILoc il;//ILOC����
	//�����յ��м����ת��ΪILOC����
	Selector sl(code,il);//ָ��ѡ����
	sl.select();
	//��ILOC������п����Ż�
	//PeepHole ph(il);//�����Ż���
//#ifdef PEEP
	//if(Args::opt)ph.filter();//�Ż����˴���
//#endif

	//���Ż����ILOC�������Ϊ������
	il.outPut(file);
}

/*
	��ȡ���ջ֡���
*/
int Fun::getMaxDep()
{
	return maxDepth;
}

/*
	�������ջ֡���
*/
void Fun::setMaxDep(int dep)
{
	maxDepth=dep;
	//���ú���ջ֡���ض�λ��ǣ��������ɲ�ͬ��ջ֡��������
	relocated=true;
}

/*
	����ջ֡�����¶�λ�ˣ�
*/
bool Fun::isRelocated()
{
	return relocated;
}




