#include "livevar.h"
#include "dfg.h"
#include "intercode.h"
#include "symbol.h"
#include "symtab.h"

LiveVar::LiveVar(DFG*g,SymTab*t,vector<Var*>&paraVar):dfg(g),tab(t)
{
	//���������������ȫ�ֱ�����������������
	varList=tab->getGlbVars();//ȫ�ֱ���
	int glbNum=varList.size();//ȫ�ֱ�������
	for(unsigned int i=0;i<paraVar.size();++i)
		varList.push_back(paraVar[i]);//�����������б�
	dfg->toCode(optCode);//��ȡ�м����
	//ͳ�����еľֲ�����
	for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
		InterInst*inst=*i;//����ָ��
		Operator op=inst->getOp();//��ȡ������
		if(op==OP_DEC){//�ֲ���������
			varList.push_back(inst->getArg1());//��¼����
		}
	}
	U.init(varList.size(),1);//��ʼ����������,ȫ��
	E.init(varList.size(),0);//��ʼ����������,�ռ�
	G=E;//��ʼ��
	for(int i=0;i<glbNum;i++)G.set(i);//��ʼ��ȫ�ֱ�������
	for(unsigned int i=0;i<varList.size();i++)//�������б���
	{
		varList[i]->index=i;//��¼�������б�����
	}
	//��ʼ��ָ���ָ���use��def����
	for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
		InterInst*inst=*i;//����ָ��
		inst->liveInfo.use=E;//��ʼ��ʹ�ü�����ɱ������
		inst->liveInfo.def=E;
		Var*rs=inst->getResult();//��ȡ���
		Operator op=inst->getOp();//��ȡ������
		Var*arg1=inst->getArg1();//��ȡ������1
		Var*arg2=inst->getArg2();//��ȡ������2
		if(op>=OP_AS&&op<=OP_LEA){//��������
			inst->liveInfo.use.set(arg1->index);//ʹ��arg1
			if(arg2)
				inst->liveInfo.use.set(arg2->index);//ʹ��arg2
			if(rs!=arg1 && rs!=arg2)
				inst->liveInfo.def.set(rs->index);//��ֵresult
		}
		else if(op==OP_DEC){
			//inst->liveInfo.def.set(arg1->index);//������䶨ֵarg1
		}
		else if(op==OP_SET){//*arg1=result
			inst->liveInfo.use.set(rs->index);//��Ȼʹ����result
			//inst->liveInfo.def=E;//���ܶ�ֵ���ĸ������������������������Ļ�Ծ��Ϣ
			//inst->liveInfo.def.reset(rs->index);//���Ǿ��Բ����ܶ�ֵresult��
		}
		else if(op==OP_GET){//result=*arg1
			inst->liveInfo.use=U;//����ʹ�����κα�����������Ϊʹ�������б���
			//inst->liveInfo.def=E;//��ȷ���Ƿ��result��ֵ����������Ծ��Ϣ��arg����ָ��result
		}
		else if(op==OP_RETV){//return arg1
			inst->liveInfo.use.set(arg1->index);
		}
		else if(op==OP_ARG){//arg arg1
			if(arg1->isBase())
				inst->liveInfo.use.set(arg1->index);//��������Ϊʹ��
			else{
				inst->liveInfo.use=U;//����ʹ��ȫ���ı���
				//������Ϊû��ɱ�����б���
			}
		}
		else if(op==OP_CALL||op==OP_PROC){//[result]=arg1()
			inst->liveInfo.use=G;//����ʹ�������е�ȫ�ֱ���
			//������Ϊû��ɱ�����б���
			if(rs){
				if(rs->getPath().size()>1){//�з���ֵ,�ҷ���ֵ����ȫ�ֱ���
					inst->liveInfo.def.set(rs->index);//��ֵ�˷���ֵresult
				}
			}
		}
		else if(op==OP_JF||op==OP_JT){//if([!]arg1)goto result
			inst->liveInfo.use.set(arg1->index);//ʹ������arg1
		}
	}
}

/*
	��Ծ�������ݺ�����f(x)=(x - def(B)) | use(B)
*/
bool LiveVar::translate(Block*block)
{
	Set tmp=block->liveInfo.out;//��¼B.out��Ϊ���һ��ָ�������
	//������������ÿһ��ָ��
	for(list<InterInst*>::reverse_iterator i=block->insts.rbegin();i!=block->insts.rend();++i){
		InterInst*inst=*i;//ȡ��ָ��
		if(inst->isDead)continue;//����������
		Set& in=inst->liveInfo.in;//ָ���in
		Set& out=inst->liveInfo.out;//ָ���out
		out=tmp;//����ָ���out
		in=inst->liveInfo.use | (out-inst->liveInfo.def);//ָ����ݺ���in=f(out)
		tmp=in;//�õ�ǰָ���in�����´�ʹ�õ�out
	}
	bool flag=tmp!=block->liveInfo.in;//�Ƿ�仯
	block->liveInfo.in=tmp;//�趨B.in����
	return flag;
}

/*
	��Ծ������������������
	direct : ����������,����
	init : ��ʼ������,B.in=E
	bound : �߽缯�ϣ�Exit.in=E
	join : �������㣬����
	translate : ���ݺ���,f(x)=(x - def(B)) | use(B)
*/
void LiveVar::analyse()
{
	//����Ĵ�������ʱ����ȡ����liveout���ϵ�bug
	dfg->blocks[dfg->blocks.size()-1]->liveInfo.out=E;//��ʼ���߽缯��Exit.out=E
	translate(dfg->blocks[dfg->blocks.size()-1]);//�������ڲ�ָ�����ʵ����exit
	//����������������
	dfg->blocks[dfg->blocks.size()-1]->liveInfo.in=E;//��ʼ���߽缯��Exit.in=E
	for(unsigned int i=0;i<dfg->blocks.size()-1;++i){
		dfg->blocks[i]->liveInfo.in=E;//��ʼ������������B.in=E
	}
	bool change=true;//���ϱ仯���
	while(change){//B.in���Ϸ����仯
		change=false;//�����趨�仯���
		for(int i=dfg->blocks.size()-2;i>=0;--i){//��������B!=Exit
			if(!dfg->blocks[i]->canReach)continue;//�鲻�ɴﲻ����
			Set tmp=E;//���潻��������
			for(list<Block*>::iterator j=dfg->blocks[i]->succs.begin();
				j!=dfg->blocks[i]->succs.end();++j){//succ[i]
				tmp=tmp | (*j)->liveInfo.in;
			}
			//B.out=| succ[j].in
			dfg->blocks[i]->liveInfo.out=tmp;
			if(translate(dfg->blocks[i]))//���ݺ���ִ��ʱ�Ƚ�ǰ�󼯺��Ƿ��в��
				change=true;
		}
	}
	// /*
	// 	�������
	// */
	// for(unsigned int i=0;i<dfg->blocks.size();++i){
	// 	printf("<%d>", i);
	// 	dfg->blocks[i]->liveInfo.in.p();
	// 	printf("\t");
	// 	dfg->blocks[i]->liveInfo.out.p();
	// 	printf("\n");
	// }
}

/*
	�����ṩ��liveout������ȡ�Ż���ı������ϡ�����ͻ����
*/
vector<Var*> LiveVar::getCoVar(Set liveout)
{
	vector<Var*> coVar;
	for(unsigned int i=0;i<varList.size();i++){
		if(liveout.get(i)){
			coVar.push_back(varList[i]);//����Ծ�ı�������
		}
	}
	return coVar;
}

/*
	���ؿռ�����
*/
Set& LiveVar::getE()
{
	return E;
}

/*
	����������
*/
void LiveVar::elimateDeadCode(int stop)
{
	if(stop){//û���µ�����������,������������
		//������Щ�������ڷ��������У���¼������Ծ��
		for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
			InterInst*inst=*i;//����ָ��
			Operator op=inst->getOp();//��ȡ������
			if(inst->isDead||op==OP_DEC)continue;//���������������ָ��
			Var*rs=inst->getResult();//��ȡ���
			Var*arg1=inst->getArg1();//��ȡ������1
			Var*arg2=inst->getArg2();//��ȡ������2
			if(rs)rs->live=true;
			if(arg1)arg1->live=true;
			if(arg2)arg2->live=true;
		}
		//ɾ����Ч��DEC����
		for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
			InterInst*inst=*i;//����ָ��
			Operator op=inst->getOp();//��ȡ������
			if(op==OP_DEC){
				Var*arg1=inst->getArg1();//��ȡ������1
				if(!arg1->live)inst->isDead=true;//�������ǻ�Ծ���ˣ�DEC����Ϊ������
			}
		}
		return ;
	}

	// for (list<InterInst*>::iterator i = optCode.begin(); i != optCode.end(); ++i)
	// {
	// 	if(!(*i)->isDead)(*i)->toString();
	// }

	stop=true;//ϣ��ֹͣ
	analyse();
	
	// for(int i=0;i<varList.size();i++)
	// 	printf("%s ",varList[i]->getName().c_str());
	// printf("\n");
	
	//��ϴһ�δ���
	for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
		InterInst*inst=*i;//����ָ��
		if(inst->isDead)continue;//�����������ظ�����
		Var*rs=inst->getResult();//��ȡ���
		Operator op=inst->getOp();//��ȡ������
		Var*arg1=inst->getArg1();//��ȡ������1
		Var*arg2=inst->getArg2();//��ȡ������2
		if(op>=OP_AS&&op<=OP_LEA||op==OP_GET){//��ֵ��������
			if(rs->getPath().size()==1)continue;//ȫ�ֱ�����������
			//���ڲ���Ծ������a=a;����ʽ����Դ�ڸ�д�����Ĵ�������
			if(!inst->liveInfo.out.get(rs->index)
				||op==OP_AS&&rs==arg1){
				inst->isDead=true;
				stop=false;//ʶ���µ�������
			}
		}
		// else if(op==OP_DEC){
		// 	//���ڲ���Ծ
		// 	if(!inst->liveInfo.out.get(arg1->index))
		// 		inst->isDead=true;
		// 		stop=true;//ʶ���µ�������
		// }
		// else if(op==OP_SET){//*arg1=result
		// 	//����������
		// }
		// else if(op==OP_RETV){//return arg1
		// 	//����������
		// }
		// else if(op==OP_ARG){//arg arg1
		// 	//����������
		// }
		// else if(op==OP_PROC){
		// 	//����������
		// }
		else if(op==OP_CALL){
			//����������ֵ,����������ֵ����Ծ�����滻Ϊ����CALLָ��
			if(!inst->liveInfo.out.get(rs->index)){
				inst->callToProc();//��callָ���滻Ϊprocָ��
			}
		}
	}
	elimateDeadCode(stop);
}
