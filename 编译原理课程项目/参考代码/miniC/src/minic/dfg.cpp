#include "dfg.h"
#include "intercode.h"
#include "constprop.h"

/*******************************************************************************
                                   ������
*******************************************************************************/

/*
	�������ʼ��
*/
Block::Block(vector<InterInst*>&codes):visited(false),canReach(true)
{
	for(unsigned int i=0;i<codes.size();++i){
		codes[i]->block=this;//��¼ָ�����ڵĻ�����
		insts.push_back(codes[i]);//ת��Ϊlist
	}
}

/*
	���������ָ��
*/
void Block::toString()
{
	printf("-----------%.8x----------\n",this);
	printf("ǰ����");
	for (list<Block*>::iterator i = prevs.begin(); i != prevs.end(); ++i)
	{
		printf("%.8x ",*i);
	}
	printf("\n");
	printf("��̣�");
	for (list<Block*>::iterator i = succs.begin(); i != succs.end(); ++i)
	{
		printf("%.8x ",*i);
	}
	printf("\n");
	for (list<InterInst*>::iterator i = insts.begin(); i != insts.end(); ++i)
	{
		(*i)->toString();
	}
	printf("-----------------------------\n");
}


/*******************************************************************************
                                   ������ͼ
*******************************************************************************/

/*
	��ʼ��
*/
DFG::DFG(InterCode& code)
{
	code.markFirst();//��ʶ��ָ��
	codeList=code.getCode();//��ȡ��������
	createBlocks();//����������
	linkBlocks();//���ӻ������ϵ
}

/*
	����������
*/
void DFG::createBlocks()
{
	vector<InterInst*>tmpList;//��¼һ���������ָ����ʱ�б�
	for(unsigned int i=0;i<codeList.size();++i){
		if(tmpList.empty()&&codeList[i]->isFirst()){
			tmpList.push_back(codeList[i]);//��ӵ�һ����ָ��
			continue;
		}
		if(!tmpList.empty()){
			if(codeList[i]->isFirst()){//�µ���ָ��
				blocks.push_back(new Block(tmpList));//������ӻ�����
				tmpList.clear();//����ϸ���ʱ�б�
			}
			tmpList.push_back(codeList[i]);//����µ���ָ����߻������̵�ָ��
		}
	}
	blocks.push_back(new Block(tmpList));//������һ��������
}

/*
	���ӻ�����
*/
void DFG::linkBlocks()
{
	//���ӻ�����˳���ϵ
	for (unsigned int i = 0; i < blocks.size()-1; ++i){//��̹�ϵ
		InterInst*last=blocks[i]->insts.back();//��ǰ����������һ��ָ��
		if(!last->isJmp())//����ֱ����ת������˳��ִ��
			blocks[i]->succs.push_back(blocks[i+1]);
	}
	for (unsigned int i = 1; i < blocks.size(); ++i){//ǰ����ϵ
		InterInst*last=blocks[i-1]->insts.back();//ǰ������������һ��ָ��
		if(!last->isJmp())//����ֱ����ת������˳��ִ��
			blocks[i]->prevs.push_back(blocks[i-1]);
	}
	for (unsigned int i = 0; i < blocks.size(); ++i){//��ת��ϵ
		InterInst*last=blocks[i]->insts.back();//����������һ��ָ��
		if(last->isJmp()||last->isJcond()){//��ֱ��/��������ת
			blocks[i]->succs.push_back(last->getTarget()->block);//��תĿ���Ϊ���
			last->getTarget()->block->prevs.push_back(blocks[i]);//�෴Ϊǰ��
		}
	}
}


/*
	������л�����
*/
DFG::~DFG()
{
	for (unsigned int i = 0; i < blocks.size(); ++i)
	{
		delete blocks[i];
	}
	for (unsigned int i = 0; i < newCode.size(); ++i)
	{
		delete newCode[i];
	}
}


/*
	���Կ��Ƿ�ɴ�
*/
bool DFG::reachable(Block*block)
{
	if(block==blocks[0])return true;//�������
	else if(block->visited)return false;//���ʹ���
	block->visited=true;//�趨���ʱ��
	bool flag=false;//�ɴ���ڱ��
	//����ǰ��,����ÿ��ǰ��
	for(list<Block*>::iterator i=block->prevs.begin();i!=block->prevs.end();++i){
		Block*prev=*i;//ÿ��ǰ��
		flag=reachable(prev);//�ݹ����
		if(flag)break;//�ɵ��������ֹ���ԣ����������������ǰ��
	}	
	return flag;//���ر��
}

/*
	����鲻�ɴ��ɾ�����к�̣��������������к��
*/
void DFG::release(Block*block)
{	
	//����block�Ƿ�����ڵ�ɴ�	
	if(!reachable(block)){//ȷ��Ϊ���ɴ����
		list<Block*> delList;
		for(list<Block*>::iterator i=block->succs.begin();i!=block->succs.end();++i){
			delList.push_back(*i);//��¼���к��
		}
		//��ɾ������뵱ǰ��Ĺ�ϵ
		for(list<Block*>::iterator i=delList.begin();i!=delList.end();++i){
			block->succs.remove(*i);
			(*i)->prevs.remove(block);
		}
		//�ٵݹ鴦�����к��
		for(list<Block*>::iterator i=delList.begin();i!=delList.end();++i){
			release(*i);//�ݹ�ɾ��end�ĺ��
		}
	}
}


/*
	ɾ�������ϵ������鲻�ɴ��ɾ�����к����ϵ
*/
void DFG::delLink(Block*begin,Block*end)
{
	resetVisit();
	//���begin��end�Ĺ���
	if(begin){//endû��ǰ�������
		begin->succs.remove(end);
		end->prevs.remove(begin);
	}
	release(end);//�ݹ�����������Ҫ���Ժ�̿��Ƿ�ɴ�
}

/*
	���÷��ʱ��
*/
void DFG::resetVisit()
{
	//���÷��ʱ��
	for (unsigned int i = 0; i < blocks.size(); ++i)
	{
		blocks[i]->visited=false;
	}
}


/*
	����������ͼΪ�м����
*/
void DFG::toCode(list<InterInst*>& opt)
{
	opt.clear();
	for (unsigned int i = 0; i < blocks.size(); ++i)
	{
		resetVisit();
		if(reachable(blocks[i])){//��Ч�Ļ�����
			list<InterInst*> tmpInsts;//����һ��ָ���ֹ����ɾ��
			for(list<InterInst*>::iterator it=blocks[i]->insts.begin();
				it!=blocks[i]->insts.end();++it){
				if((*it)->isDead)continue;//����������
				tmpInsts.push_back(*it);//��ȡ��Чָ��
			}
			opt.splice(opt.end(),tmpInsts);//�ϲ���Ч������
		}
		else
			blocks[i]->canReach=false;//��¼�鲻�ɴ�
	}
}

/*
	���������
*/
void DFG::toString()
{
	for (unsigned int i = 0; i < blocks.size(); ++i)
	{
		blocks[i]->toString();
	}
}
