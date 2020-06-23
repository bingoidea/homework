#include "alloc.h"
#include "intercode.h"
#include "livevar.h"
#include <algorithm>
#include "symbol.h"
#include "platform.h"

/*******************************************************************************
                                   �ڵ�
*******************************************************************************/

Node::Node(Var*v,Set& E):var(v),degree(0),color(-1)
{
	exColors=E;//�ų�ɫ����Ϊ��
}

/*
	���һ���ߣ�������룬��+1����֤���ֲ���
*/
void Node::addLink(Node*node)
{
	vector<Node*>::iterator pos=lower_bound(links.begin(),links.end(),node);
	if(pos==links.end() || *pos!=node){//û���ҵ��������
		links.insert(pos,node);
		degree++;//������
		//printf("\t%s  ---  %s\n", var->getName().c_str(),node->var->getName().c_str());
	}
}

/*
	���һ���ų�ɫ,��-1
*/
void Node::addExColor(int color)
{
	if(degree==-1)return;//�Ѿ���ɫ�ڵ㣬���ٴ���
	exColors.set(color);//����ų�ɫ
	degree--;//�ȼ���
}

/*
	����exColorsѡ���һ����Ч����ɫ����=-1
*/
void Node::paint(Set& colorBox)
{
	Set availColors=colorBox-exColors;//���õ���ɫ����
	for(int i=0;i<availColors.count;i++){//�������п�����ɫ
		if(availColors.get(i)){//������ɫ����
			color=i;//��ɫ��
			var->regId=color;//��¼��ɫ���Ĵ���ID��������
			degree=-1;//����ΪС���κ�һ��δ����ڵ�Ķ�ֵ��������֤�����ظ����ʡ���ÿ��ѡ��Ƚڵ㣡
			for(int j=0;j<links.size();j++){//�����ھ�
				links[j]->addExColor(color);//�ھ�����ų�ɫ
			}
			return ;//��ɫ�ɹ���
		}
	}
	degree=-1;//�Ѿ�������ɫ��δ�ɹ������Ϊ����ڵ�
	//��ɫʧ�ܣ�����
}

/*******************************************************************************
                                   ������
*******************************************************************************/

Scope::Scope(int i,int addr):id(i),esp(addr),parent(NULL)
{}

Scope::~Scope()
{
	for(unsigned int i=0;i<children.size();i++)
		delete children[i];
}

/*
	����i�����򣬲����������һ����������id=i��esp�̳е�ǰ��esp
*/
Scope* Scope::find(int i)
{
	//���ֲ���
	Scope*sc=new Scope(i,esp);//�ȴ����������򣬿�����esp
	vector<Scope*>::iterator pos=lower_bound(children.begin(),children.end(),sc,scope_less());
	if(pos==children.end() || (*pos)->id!=i){//û���ҵ��������
		children.insert(pos,sc);//�������
		sc->parent=this;//��¼���ڵ�
	}
	else{
		delete sc;//ɾ�����Ҷ���
		sc=*pos;//�ҵ���
	}
	return sc;
}


/*******************************************************************************
                                   ��ͻͼ
*******************************************************************************/

/*
	���캯��
*/
CoGraph::CoGraph(list<InterInst*>&optCode,vector<Var*>&para,LiveVar*lv,Fun*f)
{
	fun=f;
	this->optCode=optCode;//��¼����
	this->lv=lv;//��¼��Ծ������������ָ��
#ifdef REG
	U.init(Plat::regNum,1);//��ʼ����ɫ����,ȫ��
	E.init(Plat::regNum,0);//��ʼ����ɫ����,�ռ�
#else
	U.init(0,1);//��ʼ����ɫ����,ȫ��
	E.init(0,0);//��ʼ����ɫ����,�ռ�
#endif

	//������������
	for(unsigned int i=0;i<para.size();++i)
		varList.push_back(para[i]);//�����������б�
	//���еľֲ�����
	for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
		InterInst*inst=*i;//����ָ��
		Operator op=inst->getOp();//��ȡ������
		if(op==OP_DEC){//�ֲ���������
			Var* arg1=inst->getArg1();
			//if(arg1->getArray())continue;//����Ϊ�������Ĵ���
			varList.push_back(arg1);//��¼����
		}
		if(op==OP_LEA){//���ֻ�ܷ����ڴ�ı�����
			Var* arg1=inst->getArg1();
			if(arg1)arg1->inMem=true;//p=&a, aֻ�ܷ����ڴ�
		}
	}
	Set& liveE=lv->getE();//��Ծ��������ʱ�Ŀռ���
	//���㵱ǰ�����б�����ڻ�Ծ��������ʱ�����б������
	Set mask=liveE;//��ʼ��Ϊ�ռ�
	for(unsigned int i=0;i<varList.size();i++){//������ǰ�����б�
		mask.set(varList[i]->index);//ȡ�������ڻ�Ծ��������ʱ���б�����
	}
	//����ͼ�ڵ�
	for(unsigned int i=0;i<varList.size();i++){
		Node*node;
		if(varList[i]->getArray()||varList[i]->inMem)//�������ֻ�����ڴ�ı���������ɫ
			node=new Node(varList[i],U);//��������Ľڵ�
		else
			node=new Node(varList[i],E);//���������Ľڵ�
		varList[i]->index=i;//�����µı����б�������������ұ������ڵ��µ��б�λ�ã�
		nodes.push_back(node);//����ڵ�
	}
	// printf("varList:");
	// for(unsigned int i=0;i<varList.size();i++)
	// 	printf("%s ",varList[i]->getName().c_str() );
	// printf("\nmask=");mask.p();printf("\n");
	//������ͻ��
	Set buf=liveE;//�����ϴδ����live.out���ϣ�����ƥ������
	//�������live.out����
	for(list<InterInst*>::reverse_iterator i=optCode.rbegin();i!=optCode.rend();++i){
		Set& liveout=(*i)->liveInfo.out;//live.out����
		//(*i)->toString();
		if(liveout!=buf){//�µĳ�ͻ��ϵ
			buf=liveout;//����
			//����ָ���Ծ��������������ȫͼ�ıߣ�����ͨ��������������漯�ϡ��ķ�ʽ���ټ���
			//printf("\tliveout=");liveout.p();printf("\n");
			vector<Var*> coVar=lv->getCoVar(liveout & mask);;//��ͻ�������У���ʹ���������
			for(int j=0;j<(int)coVar.size()-1;j++){//n(n-1)/2�����
				for(int k=j+1;k<coVar.size();k++){
					nodes[coVar[j]->index]->addLink(nodes[coVar[k]->index]);//��ӹ�ϵ�������ظ����
					nodes[coVar[k]->index]->addLink(nodes[coVar[j]->index]);//�໥��ӹ�ϵ
					// for(unsigned int i=0;i<nodes.size();i++){
					// 	printf("\t%s(%d) ", nodes[i]->var->getName().c_str(),nodes[i]->degree);
					// }printf("\n");
				}
			}
		}
	}
}

/*
	��������
*/
CoGraph::~CoGraph()
{
	for(unsigned int i=0;i<nodes.size();i++){
		delete nodes[i];//����ڵ��ڴ�
	}
	delete scRoot;//����������ڴ�
}


/*
	ѡ�������δ����ڵ㣬�������Ѹ��ݽڵ�ȶ�����
*/
Node* CoGraph::pickNode()
{
	//ͼ�ڵ�ȷ����仯�����¹�������
	make_heap(nodes.begin(),nodes.end(),node_less());//��С����O(NlogN) N-->0
	// for(unsigned int i=0;i<nodes.size();i++){
	// 	printf("\t%s(%d) ", nodes[i]->var->getName().c_str(),nodes[i]->degree);
	// }
	// printf("\n");
	Node*node=nodes.front();//ȡ���Ƚڵ�
	//printf("\t<--%s\n", node->var->getName().c_str());
	return node;
}

/*
	�Ĵ�������ͼ��ɫ�㷨,��regNum���Ĵ�����ɫ��ͼ��
*/
void CoGraph::regAlloc()
{
	Set colorBox=U;//��ɫ����
	int nodeNum=nodes.size();//�ڵ����
	for(int i=0;i<nodeNum;i++){//�������нڵ�
		Node* node=pickNode();//ѡȡδ��������Ƚڵ�
		node->paint(colorBox);//�Ըýڵ���ɫ
	}
}

/*
	��ӡ������
*/
void CoGraph::printTree(Scope*root,bool tree_style)
{
	if(!tree_style){
		//���Ŵ�ӡ
		printf("( <%d>:%d ", root->id,root->esp);
		for (int i = 0; i < root->children.size(); ++i)
		{
			printTree(root->children[i],false);
		}
		printf(") ");	
	}
	else{//���δ�ӡ
		int y=0;//��0�п�ʼ
		__printTree(root,0,0,y);//���δ�ӡ��
	}
}

/*
	���δ�ӡ������
*/
void CoGraph::__printTree(Scope*root,int blk,int x,int& y)
{
	//��¼��ӡλ��
	root->x=x;
	root->y=y;
	//��䲻��������
	if(root->parent){//�и��ڵ�
		vector<Scope*>& brother=root->parent->children;//�ֵܽڵ�
		vector<Scope*>::iterator pos;//λ��
		pos=lower_bound(brother.begin(),brother.end(),root,Scope::scope_less());//����λ�ã�һ������
		if(pos!=brother.begin()){//���ǵ�һ���ֵ�
			Scope* prev=(*--pos);//ǰһ���ֵ�
			int disp=root->y-prev->y-1;//���ֵ
			printf("\033[s");//������λ��
			while(disp--){//��ͣ���ƶ���꣬���|
				printf("\033[1A");//����
				printf("|");//��ӡ|
				printf("\033[1D");//���ƻظ����λ��
			}
			printf("\033[u");//�ָ����λ��
		}
	}
	printf("|����\033[33m<%d>:%d\033[0m", root->id,root->esp);
	printf("\n");
	x+=(blk+1)*4;//����յ��и���
	for (int i = 0; i < root->children.size(); ++i)
	{
		++y;//ͬ���ڵ��ۼ���
		int t=blk;while(t--)printf("    ");
		printf("    ");__printTree(root->children[i],blk+1,x,y);
	}
}

/*
	���ݵ�ǰ������������·����ȡջ֡ƫ�Ƶ�ַ
*/
int& CoGraph::getEsp(vector<int>& path)
{
	//printTree(scRoot);
	Scope* scope=scRoot;//��ǰ�������ʼ��Ϊȫ��������
	for(unsigned int i=1;i<path.size();i++){//����·��
		scope=scope->find(path[i]);//����Ѱ��������û�л��Զ�������
	}
	// for (int i = 0; i < path.size(); ++i)
	// {
	// 	printf("/%d",path[i] );
	// }
	return scope->esp;//�����������ƫ�Ƶ�����
}


/*
	Ϊ������ɫ�ı�������ջ֡��ַ
*/
void CoGraph::stackAlloc()
{
	int base=Plat::stackBase_protect;//�Ĵ����������Ҫ�����ֳ���ʹ�ñ����ֳ�ջ֡��ַ
	//��ʼ������������
	scRoot=new Scope(0,base);//ȫ��������,ջ��ʼƫ��Ϊebp-base
	int max=base;//��¼ջ֡�������ȣ���ʼ��Ϊbase����ֹû���ڴ����ʱ���ֵ����
	//�������е�DEC��ARGָ��
	for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
		InterInst*inst=*i;//����ָ��
		Operator op=inst->getOp();//��ȡ������
		if(op==OP_DEC){//�ֲ���������
			Var* arg1=inst->getArg1();
			if(arg1->regId==-1){//û�з��䵽�Ĵ���������ջ֡��ַ
				int& esp=getEsp(arg1->getPath());//��ȡ������Ӧ�������esp����
				int size=arg1->getSize();
				size+=(4-size%4)%4;//����4�ֽڵĴ�С����������ֲ�����
				esp+=size;//�ۼƵ�ǰ�������С
				arg1->setOffset(-esp);//�ֲ�����ƫ��Ϊ����
				if(esp>max)max=esp;
				//printf(" => esp=%d\n",-esp);
			}
		}
		//������ͨ����������ͨ��push��ջ
		// else if(op==OP_ARG){//������ջָ��
		// 	int& esp=getEsp(inst->path);//��ȡARGָ���Ӧ������,�������esp����
		// 	//����4�ֽڵĴ�С����������ֲ�����
		// 	esp+=4;//�ۼƵ�ǰ�������С�������ñ���ƫ�ƣ���Ϊarg����ֻ��ռλ
		// 	inst->offset=-esp;//����ARGָ���趨���ڴ��ַ
		// 	if(esp>max)max=esp;
		// 	//printf(" => esp=%d\n",-esp);
		// }
	}
	//���ú��������ջ֡���
	fun->setMaxDep(max);
}

/*
	�����㷨
*/
void CoGraph::alloc()
{
	regAlloc();//�Ĵ�������
	stackAlloc();//ջ֡��ַ����
	
	///////////////////////////////����������
	// printf("�Ĵ�������=%d\n",Plat::regNum);
	// for(unsigned int i=0;i<varList.size();i++){
	// 	Var* v=varList[i];
	// 	if(v->regId!=-1){//�ڼĴ���
	// 		printf("%s\treg=%d\n",v->getName().c_str(),v->regId);
	// 	}
	// 	else{//���ڴ�
	// 		printf("%s\t[ebp%c%d]\n",v->getName().c_str(),v->getOffset()<0?0:'+',v->getOffset());
	// 	}
	// }
	/////////////////////////////////�±�������ӡ���Դ���
	// printTree(scRoot);
	// int a[][10]={
	// 	{1,2,3,4,5},
	// 	{1,2,3,6,7},
	// 	{1,8},
	// 	{1,9},
	// 	{1,9,10,11},
	// 	{1,9,10,12,13},
	// 	{14,15},
	// 	{16}
	// };
	// for(int i=0;i<sizeof(a)/sizeof(a[0]);i++){
	// 	vector<int> path;
	// 	path.push_back(0);
	// 	for(int j=0;a[i][j];j++)
	// 		path.push_back(a[i][j]);
	// 	getEsp(path);
	// }
	// printTree(scRoot);
}