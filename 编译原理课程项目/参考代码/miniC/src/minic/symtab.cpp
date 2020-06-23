#include "symtab.h"
#include "error.h"
#include "symbol.h"
#include "genir.h"
#include "compiler.h"

//��ӡ�������
#define SEMERROR(code,name) Error::semError(code,name)

/*******************************************************************************
                                   ���ű�
*******************************************************************************/

Var* SymTab::voidVar=NULL;//��������ĳ�ʼ��
Var* SymTab::zero=NULL;//��������ĳ�ʼ��
Var* SymTab::one=NULL;//��������ĳ�ʼ��
Var* SymTab::four=NULL;//��������ĳ�ʼ��

/*
	��ʼ�����ű�
*/
SymTab::SymTab()
{
	/*
		�˴���������ĳ���void��1,4
	*/
	voidVar=new Var();//void����
	zero=new Var(1);//����0
	one=new Var(1);//����1
	four=new Var(4);//����4
	addVar(voidVar);//�÷��ű������Щ�������
	addVar(one);//�÷��ű������Щ�������
	addVar(zero);//�÷��ű������Щ�������
	addVar(four);//�÷��ű������Щ�������

	scopeId=0;
	curFun=NULL;
	ir=NULL;
	scopePath.push_back(0);//ȫ��������
}

/*
	�����Ϣ
*/
SymTab::~SymTab()
{
	//�������,��֤������Ϣ��ָ�����ʱ����
	hash_map<string, Fun*, string_hash>::iterator funIt,funEnd=funTab.end();
	for(funIt=funTab.begin();funIt!=funEnd;++funIt){
		delete funIt->second;
	}
	//�������
	hash_map<string, vector< Var* > *, string_hash>::iterator varIt,varEnd=varTab.end();
	for(varIt=varTab.begin();varIt!=varEnd;++varIt){
		vector<Var*>&list=*varIt->second;
		for(int i=0;i<list.size();i++)
			delete list[i];
		delete &list;
	}
	//�����
	hash_map<string, Var*, string_hash>::iterator strIt,strEnd=strTab.end();
	for(strIt=strTab.begin();strIt!=strEnd;++strIt)
		delete strIt->second;
}

/*
	�����м����������
*/
void SymTab::setIr(GenIR*ir)
{
	this->ir=ir;
}

/*
	��ȡscopePath
*/
vector<int>& SymTab::getScopePath()
{
	return scopePath;
}

/*
	���һ�����������ű�
*/
void SymTab::addVar(Var* var)
{
	if(varTab.find(var->getName())==varTab.end()){ //û�и����ֵı���
		varTab[var->getName()]=new vector<Var*>;//��������
		varTab[var->getName()]->push_back(var);//��ӱ���
		varList.push_back(var->getName());
	}
	else{
		//�ж�ͬ�������Ƿ񶼲���һ��������
		vector<Var*>&list=*varTab[var->getName()];
		int i;
		for(i=0;i<list.size();i++)
			if(list[i]->getPath().back()==var->getPath().back())//��һ�������򣬳�ͻ��
				break;
		if(i==list.size()||var->getName()[0]=='<')//û�г�ͻ
			list.push_back(var);
		else{
			//ͬһ���������ͬ���ı����Ķ��壬extern�������ⲿ�ļ��ı������൱�ڶ����˸�ȫ�ֱ���
			SEMERROR(VAR_RE_DEF,var->getName());
			delete var;
			return;//��Ч������ɾ��������λ
		}
	}
	if(ir){
		int flag=ir->genVarInit(var);//����������ʼ�����,��������0
		if(curFun&&flag)curFun->locate(var);//����ֲ�������ջ֡ƫ��
	}
}
/*
	���һ���ַ�������
*/
void SymTab::addStr(Var* v)
{
	strTab[v->getName()]=v;
}

/*
	��ȡһ������
*/
Var* SymTab::getVar(string name)
{
	Var*select=NULL;//���ѡ��
	if(varTab.find(name)!=varTab.end()){
		vector<Var*>&list=*varTab[name];
		int pathLen=scopePath.size();//��ǰ·������
		int maxLen=0;//�Ѿ�ƥ�����󳤶�
		for(int i=0;i<list.size();i++){
			int len=list[i]->getPath().size();
			//���ֺ�ѡ�ı���,·�����Լ���ǰ׺
			if(len<=pathLen&&list[i]->getPath()[len-1]==scopePath[len-1]){
				if(len>maxLen){//ѡȡ�ƥ��
					maxLen=len;
					select=list[i];
				}
			}
		}
	}
	if(!select)SEMERROR(VAR_UN_DEC,name);//����δ����
	return select;
}

/*
	��ȡ����ȫ�ֱ���
*/
vector<Var*> SymTab::getGlbVars()
{
	vector<Var*> glbVars;
	for(int i=0;i<varList.size();i++){//���������б�
		string varName=varList[i];
		if(varName[0]=='<')continue;//���Գ���
		vector<Var*>&list=*varTab[varName];
		for(int j=0;j<list.size();j++){
			if(list[j]->getPath().size()==1){//ȫ�ֵı���
				glbVars.push_back(list[j]);
				break;//��������һ��ͬ��ȫ�ֱ���
			}
		}
	}
	return glbVars;
}


/*
	����ʵ�ʲ�������ȡһ������
*/
Fun* SymTab::getFun(string name,vector<Var*>& args)
{
	if(funTab.find(name)!=funTab.end()){
		Fun* last=funTab[name];
		if(!last->match(args)){
			SEMERROR(FUN_CALL_ERR,name);//�в�ʵ�β�ƥ��
			return NULL;
		}
		return last;
	}
	SEMERROR(FUN_UN_DEC,name);//����δ����
	return NULL;
}

/*
	��ȡ��ǰ�����ĺ���
*/
Fun* SymTab::getCurFun()
{
	return curFun;
}

/*
	����һ������
*/
void SymTab::decFun(Fun* fun)
{
	fun->setExtern(true);
	if(funTab.find(fun->getName())==funTab.end()){ //û�и����ֵĺ���
		funTab[fun->getName()]=fun;//��Ӻ���
		funList.push_back(fun->getName());
	}
	else{
		//�ж��Ƿ����ظ���������
		Fun* last=funTab[fun->getName()];
		if(!last->match(fun)){
			SEMERROR(FUN_DEC_ERR,fun->getName());//���������붨�岻ƥ��
		}
		delete fun;
	}
}

/*
	����һ������
*/
void SymTab::defFun(Fun* fun)
{
	if(fun->getExtern()){//extern����������ڶ���
		SEMERROR(EXTERN_FUN_DEF,fun->getName());
		fun->setExtern(false);
	}
	if(funTab.find(fun->getName())==funTab.end()){ //û�и����ֵĺ���
		funTab[fun->getName()]=fun;//��Ӻ���
		funList.push_back(fun->getName());
	}
	else{//�Ѿ�����
		Fun*last=funTab[fun->getName()];
		if(last->getExtern()){
			//֮ǰ������
			if(!last->match(fun)){//ƥ�������
				SEMERROR(FUN_DEC_ERR,fun->getName());//���������붨�岻ƥ��
			}
			last->define(fun);//�����������������趨externedΪfalse
		}
		else{//�ض���
			SEMERROR(FUN_RE_DEF,fun->getName());
		}
		delete fun;//ɾ����ǰ��������
		fun=last;//���ú����ṹ��
	}
	curFun=fun;//��ǰ�����ĺ���
	ir->genFunHead(curFun);//�����������
}

/*
	��������һ������
*/
void SymTab::endDefFun()
{
	ir->genFunTail(curFun);//������������
	curFun=NULL;//��ǰ�����ĺ����ÿ�
}

/*
	���һ���м����
*/
void SymTab::addInst(InterInst*inst)
{
	if(curFun)curFun->addInst(inst);
	else delete inst;
}

/*
	����ֲ�������
*/
void SymTab::enter()
{
	scopeId++;
	scopePath.push_back(scopeId);
	if(curFun)curFun->enterScope();
}

/*
	�뿪�ֲ�������
*/
void SymTab::leave()
{
	scopePath.pop_back();//��������
	if(curFun)curFun->leaveScope();
}

/*
	ִ���Ż�����
*/
/*
void SymTab::optimize()
{
	for(int i=0;i<funList.size();i++){
		funTab[funList[i]]->optimize(this);
	}
}
*/

/*
	������ű���Ϣ
*/
void SymTab::toString()
{
	printf("----------������----------\n");
	for(int i=0;i<varList.size();i++){
		string varName=varList[i];
		vector<Var*>&list=*varTab[varName];
		printf("%s:\n",varName.c_str());
		for(int j=0;j<list.size();j++){
			printf("\t");
			list[j]->toString();
			printf("\n");
		}
	}
	printf("----------����-----------\n");
	hash_map<string, Var*, string_hash>::iterator strIt,strEnd=strTab.end();
	for(strIt=strTab.begin();strIt!=strEnd;++strIt)
		printf("%s=%s\n",strIt->second->getName().c_str(),strIt->second->getStrVal().c_str());
	printf("----------������----------\n");
	for(int i=0;i<funList.size();i++){
		funTab[funList[i]]->toString();
	}
}

/*
	����м����
*/
void SymTab::printInterCode()
{
	for(int i=0;i<funList.size();i++){
		funTab[funList[i]]->printInterCode();
	}
}

/*
	����Ż����м����
*/
/*void SymTab::printOptCode()
{
	for(int i=0;i<funList.size();i++){
		funTab[funList[i]]->printOptCode();
	}
}
*/

void SymTab::genData(FILE*file)
{
	//���ɳ����ַ���,.rodata��
	fprintf(file, ".section .rodata\n");
	hash_map<string, Var*, string_hash>::iterator strIt,strEnd=strTab.end();
	for(strIt=strTab.begin();strIt!=strEnd;++strIt){
		Var*str=strIt->second;//�����ַ�������
		fprintf(file, "%s:\n", str->getName().c_str());//var:
		fprintf(file, "\t.ascii \"%s\"\n", str->getRawStr().c_str());//.ascii "abc\000"
	}
	//�������ݶκ�bss��
	fprintf(file, ".data\n");
	vector<Var*> glbVars=getGlbVars();//��ȡ����ȫ�ֱ���
	for(unsigned int i=0;i<glbVars.size();i++)
	{
		Var*var=glbVars[i];
		fprintf(file, "\t.global %s\n",var->getName().c_str());//.global var
		if(!var->unInit()){//������ʼ����,�������ݶ�
			fprintf(file, "%s:\n", var->getName().c_str());//var:
			if(var->isBase()){//�������ͳ�ʼ�� 100 'a'
				const char* t=var->isChar()?".byte":".word";
				fprintf(file, "\t%s %d\n", t, var->getVal());//.byte 65  .word 100
			}
			else{//�ַ�ָ���ʼ��
				fprintf(file, "\t.word %s\n",var->getPtrVal().c_str());//.word .L0
			}
		}
		else{//����bss��
			fprintf(file, "\t.comm %s,%d\n", var->getName().c_str(), var->getSize());//.comm var,4
		}
	}
}

/*
	�������ļ�
*/
void SymTab::genAsm(char*fileName)
{
	//��.c�滻Ϊ.o������ֱ��׷��.o
	string newName=fileName;
	int pos=newName.rfind(".c");
	if(pos>0&&pos==newName.length()-2){
		newName.replace(pos,2,".s");
	}
	else newName=newName+".s";
	FILE* file=fopen(newName.c_str(),"w");//��������ļ�
	//�������ݶ�
	genData(file);
	//���ɴ����
	//if(Args::opt)fprintf(file,"#�Ż�����\n");
	//fprintf(file,"#δ�Ż�����\n");
	//fprintf(file,".text\n");
	for(int i=0;i<funList.size();i++){
		//printf("-------------���ɺ���<%s>--------------\n",funTab[funList[i]]->getName().c_str());
		funTab[funList[i]]->genAsm(file);
	}
	fclose(file);
}







