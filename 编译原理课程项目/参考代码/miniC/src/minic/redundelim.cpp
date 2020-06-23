#include <algorithm>
#include "redundelim.h"
#include "dfg.h"
#include "intercode.h"
#include "symbol.h"
#include "symtab.h"

/*******************************************************************************
                                   ���ʽ����
*******************************************************************************/
/*
	���캯��
*/
Expr::Expr(Var*r,Operator o,Var*a1,Var*a2)
	:rs(r),newRs(NULL),op(o),arg1(a1),arg2(a2),index(-1)
{}

/*
	���ʽ��ͬ
*/
bool Expr::operator==(Expr&e)
{
	return op==e.op&&arg1==e.arg1&&arg2==e.arg2;
}

/*
	�������ؽ��
*/
Var* Expr::genResult(SymTab*tab)
{
	if(newRs)return newRs;//���ظ�����
	vector<int> glbPath;//�����ڵ�һ������
	glbPath.push_back(0);//ȫ��
	glbPath.push_back(rs->getPath()[1]);//������
	newRs=new Var(glbPath,rs);//�����µı�����������Ϊ������һ������
	tab->addVar(newRs);//��ӵ����ű�
}

/*
	��ȡ���ʽ����ʱ�������
*/
Var* Expr::getNewRs()
{
	return newRs;
}


/*
	��������ָ��
*/
InterInst* Expr::genInst(SymTab*tab,DFG*dfg)
{
	genResult(tab);//�������ر���
	InterInst*inst=new InterInst(op,newRs,arg1,arg2);//����ָ��
	dfg->newCode.push_back(inst);//���浽�´����б���
	return inst;
}

/*
	��������ָ��
*/
InterInst* Expr::genDec(DFG*dfg)
{
	if(!newRs)return NULL;//û�м�������
	InterInst*inst=new InterInst(OP_DEC,newRs);//����ָ��
	dfg->newCode.push_back(inst);
	return inst;
}


/*
	���ʽʹ���˱���v
*/
bool Expr::use(Var*v)
{
	return arg1==v||arg2==v;
}

/*******************************************************************************
                                   �ֲ���������
*******************************************************************************/
/*
	��ѯ���ʽλ��
*/
int RedundElim::findExpr(Expr&e)
{
	for(unsigned int i=0;i<exprList.size();++i)
		if(exprList[i]==e)return i;
	return -1;
}

/*
	����
*/
RedundElim::RedundElim(DFG*g,SymTab*tab):dfg(g),symtab(tab)
{
	dfg->toCode(optCode);//��ȡ�Ͻ׶��Ż���Ĵ���
	int j=0;
	//ͳ�����еı��ʽ
	for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
		InterInst*inst=*i;//����ָ��
		Var* rs=inst->getResult();//��ȡ���
		Operator op=inst->getOp();//��ȡ������
		Var*arg1=inst->getArg1();//��ȡ������1
		Var*arg2=inst->getArg2();//��ȡ������2
		if(op>=OP_ADD&&op<=OP_GET&&op!=OP_SET){//���еĿ���ʹ�õı��ʽ
			Expr tmp(rs,op,arg1,arg2);//�������ʽ����
			if(findExpr(tmp)!=-1)continue;//���ʽ�Ѿ�����
			tmp.index=j++;//��¼����
			exprList.push_back(tmp);//���浽���ʽ�б�
		}
	}
	U.init(exprList.size(),1);//��ʼ����������
	E.init(exprList.size(),0);
	//��ʼ��ָ���ָ���e_use��e_kill����
	for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
		InterInst*inst=*i;//����ָ��
		inst->e_use=E;//��ʼ��ʹ�ü�����ɱ������
		inst->e_kill=E;
		Var*rs=inst->getResult();//��ȡ���
		Operator op=inst->getOp();//��ȡ������
		Var*arg1=inst->getArg1();//��ȡ������1
		Var*arg2=inst->getArg2();//��ȡ������2
		if(op>=OP_AS&&op<=OP_GET&&op!=OP_SET){//���еĿ���ʹ�õı��ʽ
			if(op==OP_AS){//��ֵ������⴦��
				for(unsigned int i=0;i<exprList.size();++i){
					if(exprList[i].use(rs))inst->e_kill.set(i);//�趨ɱ������
				}
				continue;
			}
			Expr tmp(rs,op,arg1,arg2);
			int index=findExpr(tmp);//���ʽ�ش���
			inst->e_use.set(index);//�趨ʹ�ü���
			for(unsigned int i=0;i<exprList.size();++i){
				if(exprList[i].use(rs))inst->e_kill.set(i);//�趨ɱ������
			}
		}
		else if(inst->unknown())//����Ԥ�����
			inst->e_kill=U;//ɱ��ȫ�����ʽ
	}
	//��ʼ�����������������ڷ���֧��ڵ�
	for(unsigned int i=0;i<dfg->blocks.size();++i){
		dfg->blocks[i]->info.index=i;
	}
	BE.init(dfg->blocks.size(),0);//��ʼ�����������
	BU.init(dfg->blocks.size(),1);
}

/*
	Ԥ��ִ�б��ʽ���ݺ���:f(x)=e_use(B) & (x-e_kill(B))
*/
bool RedundElim::translate_anticipated(Block*block)
{
	Set tmp=block->info.anticipated.out;//��¼B.out��Ϊ���һ��ָ�������
	//������������ÿһ��ָ��
	for(list<InterInst*>::reverse_iterator i=block->insts.rbegin();i!=block->insts.rend();++i){
		InterInst*inst=*i;//ȡ��ָ��
		Set& in=inst->info.anticipated.in;//ָ���in
		Set& out=inst->info.anticipated.out;//ָ���out
		out=tmp;//����ָ���out
		// if(inst->e_kill.empty())
		// {
		// 	int i=0;
		// 	i++;
		// }
		in=inst->e_use | (out-inst->e_kill);//ָ����ݺ���in=f(out)
		tmp=in;//�õ�ǰָ���in�����´�ʹ�õ�out
	}
	bool flag=tmp!=block->info.anticipated.in;//�Ƿ�仯
	block->info.anticipated.in=tmp;//�趨B.in����
	return flag;
}

/*
	Ԥ��ִ�б��ʽ��������������
	direct : ����������,����
	init : ��ʼ������,B.in=U
	bound : �߽缯�ϣ�Exit.in=E
	join : �������㣬����
	translate : ���ݺ���,f(x)=e_use(B) & (x-e_kill(B))
*/
void RedundElim::analyse_anticipated()
{
	/*
		Exit�����ʼ��
		�����ڷ���anticipatedǰ�����������⣬���Exit�ڵ��out���ϲ��ܵõ����㣬
		�����ڼ���latest[Exit]ʱ����Ҫearliest[Exit]�����ʹ����anticipated[Exit],
		�ʳ�ʼ���������Ϊ�գ�
	*/
	dfg->blocks[dfg->blocks.size()-1]->info.anticipated.out=E;// ��ʼ��
	translate_anticipated(dfg->blocks[dfg->blocks.size()-1]);//����Ϣ���ݵ�ָ����
	//����������������
	dfg->blocks[dfg->blocks.size()-1]->info.anticipated.in=E;//��ʼ���߽缯��Exit.in=E
	for(unsigned int i=0;i<dfg->blocks.size()-1;++i){
		dfg->blocks[i]->info.anticipated.in=U;//��ʼ������������B.in=U
	}
	bool change=true;//���ϱ仯���
	while(change){//B.in���Ϸ����仯
		change=false;//�����趨�仯���
		for(int i=dfg->blocks.size()-2;i>=0;--i){//��������B!=Exit
			if(!dfg->blocks[i]->canReach)continue;//�鲻�ɴﲻ����
			Set tmp=U;//���潻��������
			for(list<Block*>::iterator j=dfg->blocks[i]->succs.begin();
				j!=dfg->blocks[i]->succs.end();++j){//succ[i]
				tmp=tmp & (*j)->info.anticipated.in;
			}
			//B.out=& succ[j].in
			dfg->blocks[i]->info.anticipated.out=tmp;
			if(translate_anticipated(dfg->blocks[i]))//���ݺ���ִ��ʱ�Ƚ�ǰ�󼯺��Ƿ��в��
				change=true;
		}
	}
// 	/*
// 		�������
// 	*/
// 	for(unsigned int i=0;i<dfg->blocks.size();++i){
// 		printf("%d  ", i);
// 		dfg->blocks[i]->info.anticipated.in.p();
// 		printf("  ");
// 		dfg->blocks[i]->info.anticipated.out.p();
// 		printf("\n");
// 	}
// 	for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
// 		InterInst*inst=*i;
// 		if(inst->info.anticipated.in!=E){
// 			inst->toString();
// 		}
// 	}
}

/*
	���ñ��ʽ���ݺ�����f(x)=(anticipated(B).in | x)-e_kill(B)
*/
bool RedundElim::translate_available(Block*block)
{
	Set tmp=block->info.available.in;//��¼B.in��Ϊ��һ��ָ�������
	//������������ÿһ��ָ��
	for(list<InterInst*>::iterator i=block->insts.begin();i!=block->insts.end();++i){
		InterInst*inst=*i;//ȡ��ָ��
		Set& in=inst->info.available.in;//ָ���in
		Set& out=inst->info.available.out;//ָ���out
		in=tmp;//����ָ���in
		out=(inst->info.anticipated.in | in)-inst->e_kill;//ָ����ݺ���out=f(in)
		tmp=out;//�õ�ǰָ���out�����´�ʹ�õ�in
	}
	bool flag=tmp!=block->info.available.out;//�Ƿ�仯
	block->info.available.out=tmp;//�趨B.out����
	return flag;
}

/*
	���ñ��ʽ��������������
	direct : ����������,ǰ��
	init : ��ʼ������,B.out=U
	bound : �߽缯�ϣ�Entry.out=E
	join : �������㣬����
	translate : ���ݺ���,f(x)=(anticipated(B).in | x)-e_kill(B)
*/
void RedundElim::analyse_available()
{
	/*
		Entry�����ʼ��
		�����ڷ���availableǰ�����������⣬���Entry�ڵ��in���ϲ��ܵõ����㣬
		������used����ʱ����Ҫearliset[Entry]=anticipated[Entry]-available[Entry]��
		�ʳ�ʼ���������Ϊ�գ�
	*/
	dfg->blocks[0]->info.available.in=E;//��ʼ��in����
	translate_available(dfg->blocks[0]);//����Ϣ���ݵ�ָ����
	//����������������
	dfg->blocks[0]->info.available.out=E;//��ʼ���߽缯��Entry.out=E
	for(unsigned int i=1;i<dfg->blocks.size();++i){
		dfg->blocks[i]->info.available.out=U;//��ʼ��������B.out=U
	}	
	bool change=true;//���ϱ仯���
	while(change){//B.out���Ϸ����仯
		change=false;//�����趨�仯���
		for(unsigned int i=1;i<dfg->blocks.size();++i){//����B!=Entry
			if(!dfg->blocks[i]->canReach)continue;//�鲻�ɴﲻ����
			Set tmp=U;//���潻��������
			for(list<Block*>::iterator j=dfg->blocks[i]->prevs.begin();
				j!=dfg->blocks[i]->prevs.end();++j){//prev[i]
				tmp=tmp & (*j)->info.available.out;
			}
			//B.in=& prev[j].out
			dfg->blocks[i]->info.available.in=tmp;
			if(translate_available(dfg->blocks[i]))//���ݺ���ִ��ʱ�Ƚ�ǰ�󼯺��Ƿ��в��
				change=true;
		}
	}
// 	/*
// 		�������
// 	*/
// 	for(unsigned int i=0;i<dfg->blocks.size();++i){
// 		printf("%d  ", i);
// 		dfg->blocks[i]->info.available.in.p();
// 		printf("  ");
// 		dfg->blocks[i]->info.available.out.p();
// 		printf("\n");
// 	}
// 	for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
// 		InterInst*inst=*i;
// 		if(inst->info.available.in!=E){
// 			inst->toString();
// 		}
// 	}
}

/*
	�ɺ��ӱ��ʽ���ݺ�����f(x)=(earliest(B) | x)-e_use(B)
		���У�earliest(B)=anticipated(B).in-available(B).in
*/
bool RedundElim::translate_postponable(Block*block)
{
	Set tmp=block->info.postponable.in;//��¼B.in��Ϊ��һ��ָ�������
	//������������ÿһ��ָ��
	for(list<InterInst*>::iterator i=block->insts.begin();i!=block->insts.end();++i){
		InterInst*inst=*i;//ȡ��ָ��
		Set& in=inst->info.postponable.in;//ָ���in
		Set& out=inst->info.postponable.out;//ָ���out
		in=tmp;//����ָ���in
		//����earliest
		inst->info.earliest=inst->info.anticipated.in-inst->info.available.in;
		out=(inst->info.earliest | in)-inst->e_use;//ָ����ݺ���out=f(in)
		tmp=out;//�õ�ǰָ���out�����´�ʹ�õ�in
	}
	bool flag=tmp!=block->info.postponable.out;//�Ƿ�仯
	block->info.postponable.out=tmp;//�趨B.out����
	block->info.earliest=block->info.anticipated.in-block->info.available.in;//������earliest
	return flag;
}

/*
	�ɺ��ӱ��ʽ��������������
	direct : ����������,ǰ��
	init : ��ʼ������,B.out=U
	bound : �߽缯�ϣ�Entry.out=E
	join : �������㣬����
	translate : ���ݺ���,f(x)=(earliest(B) | x)-e_use(B)
		���У�earliest(B)=anticipated(B).in-available(B).in
*/
void RedundElim::analyse_postponable()
{
	/*
		Entry�����ʼ��
		�����ڷ���postponableǰ�����������⣬���Entry�ڵ��in���ϲ��ܵõ����㣬
		������used����ʱ����Ҫpostponable[Entry],�ʳ�ʼ���������Ϊ�գ�
	*/
	dfg->blocks[0]->info.postponable.in=E;// ��ʼ��
	translate_postponable(dfg->blocks[0]);//����Ϣ���ݵ�ָ����
	//����������������
	dfg->blocks[0]->info.postponable.out=E;//��ʼ���߽缯��Entry.out=E
	for(unsigned int i=1;i<dfg->blocks.size();++i){
		dfg->blocks[i]->info.postponable.out=U;//��ʼ��������B.out=U
	}	
	bool change=true;//���ϱ仯���
	while(change){//B.out���Ϸ����仯
		change=false;//�����趨�仯���
		for(unsigned int i=1;i<dfg->blocks.size();++i){//����B!=Entry
			if(!dfg->blocks[i]->canReach)continue;//�鲻�ɴﲻ����
			Set tmp=U;//���潻��������
			for(list<Block*>::iterator j=dfg->blocks[i]->prevs.begin();
				j!=dfg->blocks[i]->prevs.end();++j){//prev[i]
				tmp=tmp & (*j)->info.postponable.out;
			}
			//B.in=& prev[j].out
			dfg->blocks[i]->info.postponable.in=tmp;
			if(translate_postponable(dfg->blocks[i]))//���ݺ���ִ��ʱ�Ƚ�ǰ�󼯺��Ƿ��в��
				change=true;
		}
	}
// 	/*
// 		�������
// 	*/
// 	for(unsigned int i=0;i<dfg->blocks.size();++i){
// 		printf("%d  ", i);
// 		dfg->blocks[i]->info.postponable.in.p();
// 		printf("  ");
// 		dfg->blocks[i]->info.postponable.out.p();
// 		printf("\n");
// 	}
// 	for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
// 		InterInst*inst=*i;
// 		if(inst->info.postponable.in!=E){
// 			inst->toString();
// 		}
// 	}
}

/*
	��ʹ�ñ��ʽ���ݺ���:f(x)=(e_use(B) | x)-latest(B)
		���У�latest(B)=(earliest(B) | postponable(B).in) &
			(e_use(B) | ~(&( earliest(B.succ[i]) | postponable(B.succ[i]).in )))
*/
bool RedundElim::translate_used(Block*block)
{
	Set tmp=block->info.used.out;//��¼B.out��Ϊ���һ��ָ�������
	//��¼��̵Ľ�������&( earliest(B.succ[i]) | postponable(B.succ[i]).in )
	//����������һ��ָ�����ʽ��Ϊearliest(B.succ[i]) | postponable(B.succ[i]).in
	Set succJoin=U;
	for(list<Block*>::iterator i=block->succs.begin();i!=block->succs.end();++i){
		succJoin=succJoin & ((*i)->info.earliest | (*i)->info.postponable.in);
	}
	//������������ÿһ��ָ��
	for(list<InterInst*>::reverse_iterator i=block->insts.rbegin();i!=block->insts.rend();++i){
		InterInst*inst=*i;//ȡ��ָ��
		Set& in=inst->info.used.in;//ָ���in
		Set& out=inst->info.used.out;//ָ���out
		out=tmp;//����ָ���out
		//����latest
		inst->info.latest=(inst->info.earliest | inst->info.postponable.in) &
			(inst->e_use | ~succJoin);
		in=(inst->e_use | out)-inst->info.latest;//ָ����ݺ���in=f(out)
		//��¼succJoin=earliest(B) | postponable(B).in����Ϊ�´�ָ��ĺ�̽�������
		succJoin=inst->info.earliest | inst->info.postponable.in;
		tmp=in;//�õ�ǰָ���in�����´�ʹ�õ�out
	}
	bool flag=tmp!=block->info.used.in;//�Ƿ�仯
	block->info.used.in=tmp;//�趨B.in����
	return flag;
}

/*
	Ԥ��ִ�б��ʽ��������������
	direct : ����������,����
	init : ��ʼ������,B.in=E
	bound : �߽缯�ϣ�Exit.in=E
	join : �������㣬����
	translate : ���ݺ���,f(x)=(e_use(B) | x)-latest(B)
		���У�latest(B)=(earliest(B) | postponable(B).in) &
			(e_use(B) | ~(&( earliest(B.succ[i]) | postponable(B.succ[i]).in )))
*/
void RedundElim::analyse_used()
{
	/*
		Exit�����ʼ��
		�����ڷ���usedǰ�����������⣬���Exit�ڵ��out���ϲ��ܵõ����㣬
		��������ʽ�������滻��ʱ����Ҫused[Exit],�ʳ�ʼ���������Ϊ�գ�
	*/
	dfg->blocks[dfg->blocks.size()-1]->info.used.out=E;// ��ʼ��
	translate_used(dfg->blocks[dfg->blocks.size()-1]);//����Ϣ���ݵ�ָ����
	//����������������
	dfg->blocks[dfg->blocks.size()-1]->info.used.in=E;//��ʼ���߽缯��Exit.in=E
	for(unsigned int i=0;i<dfg->blocks.size()-1;++i){
		dfg->blocks[i]->info.used.in=E;//��ʼ��������B.in=E
	}
	bool change=true;//���ϱ仯���
	while(change){//B.in���Ϸ����仯
		change=false;//�����趨�仯���
		for(int i=dfg->blocks.size()-2;i>=0;--i){//����B!=Exit
			if(!dfg->blocks[i]->canReach)continue;//�鲻�ɴﲻ����
			Set tmp=E;//���潻��������
			for(list<Block*>::iterator j=dfg->blocks[i]->succs.begin();
				j!=dfg->blocks[i]->succs.end();++j){//succ[i]
				tmp=tmp | (*j)->info.used.in;
			}
			//B.out=& succ[j].in
			dfg->blocks[i]->info.used.out=tmp;
			if(translate_used(dfg->blocks[i]))//���ݺ���ִ��ʱ�Ƚ�ǰ�󼯺��Ƿ��в��
				change=true;
		}
	}
	// /*
	// 	�������
	// */
	// for(unsigned int i=0;i<dfg->blocks.size();++i){
	// 	printf("%d  ", i);
	// 	dfg->blocks[i]->info.used.in.p();
	// 	printf("  ");
	// 	dfg->blocks[i]->info.used.out.p();
	// 	printf("\n");
	// }
	// for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
	// 	InterInst*inst=*i;
	// 	//x+y �� latest[B] & used[B].out������t = x+y
	// 	if((inst->info.latest & inst->info.used.out)!=E){
	// 		inst->toString();
	// 		printf("  t=x+y\n");
	// 	}
	// }
}

/*
	֧��ڵ㴫�ݺ�����f(x)=x | B
*/
bool RedundElim::translate_dom(Block*block)
{
	Set tmp=block->info.dom.in;//��¼B.in
	tmp.set(block->info.index);//���������B
	bool flag=tmp!=block->info.dom.out;//�Ƿ�仯
	block->info.dom.out=tmp;//�趨B.out����
	return flag;
}

/*
	֧��ڵ���������������
	direct : ����������,ǰ��
	init : ��ʼ������,B.out=BE
	bound : �߽缯�ϣ�Entry.out=Entry
	join : �������㣬����
	translate : ���ݺ���,f(x)=x | B
*/
void RedundElim::analyse_dom()
{
	//����������������
	dfg->blocks[0]->info.dom.out=BE;//��ʼ���߽缯��Entry.out=Entry
	dfg->blocks[0]->info.dom.out.set(dfg->blocks[0]->info.index);//��������
	for(unsigned int i=1;i<dfg->blocks.size();++i){
		dfg->blocks[i]->info.dom.out=BU;//��ʼ��������B.out=BU
	}	
	bool change=true;//���ϱ仯���
	while(change){//B.out���Ϸ����仯
		change=false;//�����趨�仯���
		for(unsigned int i=1;i<dfg->blocks.size();++i){//����B!=Entry
			if(!dfg->blocks[i]->canReach)continue;//�鲻�ɴﲻ����
			Set tmp=BU;//���潻��������
			for(list<Block*>::iterator j=dfg->blocks[i]->prevs.begin();
				j!=dfg->blocks[i]->prevs.end();++j){//prev[i]
				tmp=tmp & (*j)->info.dom.out;
			}
			//B.in=& prev[j].out
			dfg->blocks[i]->info.dom.in=tmp;
			if(translate_dom(dfg->blocks[i]))//���ݺ���ִ��ʱ�Ƚ�ǰ�󼯺��Ƿ��в��
				change=true;
		}
	}
	// /*
	// 	�������
	// */
	// for(unsigned int i=0;i<dfg->blocks.size();++i){
	// 	printf("%d  ", i);
	// 	dfg->blocks[i]->info.dom.in.p();
	// 	printf("  ");
	// 	dfg->blocks[i]->info.dom.out.p();
	// 	printf("\n");
	// }
}

/*
	��������
*/
void RedundElim::elimate()
{
	//�����ĸ�����������
	analyse_anticipated();
	analyse_available();
	analyse_postponable();
	analyse_used();

	//----------------------֧��ڵ����������λ��------------------------------------
	// //����ȡ������Ϊѭ���ڲ����������޷�ʹ�������ⲿ�ɼ�������
	// analyse_dom();//�޷�׼ȷȷ���������λ�ã�֧��ڵ�Ҳ���У�����˽���������entry��
	// //����ɾ������
	// vector<Set> delarList(exprList.size(),BU);//�洢���ʽ�����֧��ڵ㼯�Ͻ���
	// for(list<InterInst*>::iterator j=optCode.begin();j!=optCode.end();++j){
	// 	InterInst*inst=*j;
	// 	//x+y �� latest[B] & used[B].out������t = x+y
	// 	Set insert=inst->info.latest & inst->info.used.out;//������뼯��
	// 	if(insert==E)continue;
	// 	for(int i=0;i<exprList.size();++i){//�������еı��ʽ
	// 		if(insert.get(i)){//���ʽiǰ��Ҫ����t=x+y
	// 			//�󱻲���ı��ʽ���ڻ������ǰ�����Ͻ���
	// 			delarList[i]=delarList[i] & inst->block->info.dom.out;//����������֧��ڵ㼯�Ͻ���
	// 		}
	// 	}
	// }
	// //����ǰ���㷨�����������֧��ڵ�
	// vector<Block*> declarPoint(exprList.size(),NULL);//�洢���ʽ����������
	// for(unsigned int i=0;i<declarPoint.size();++i){
	// 	int index=delarList[i].max();//������λ1����
	// 	//���λ1��ʶ����Ĺ���ǰ���������������ڵĻ�����
	// 	declarPoint[i]=(index!=-1)?dfg->blocks[index]:NULL;
	// }
	//--------------------����Ϊ֧��ڵ�����������������-----------------------------
	//�������㲢����ָ��
	for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
		InterInst*inst=*i;
		//x+y �� latest[B] & used[B].out������t = x+y
		Set insert=inst->info.latest & inst->info.used.out;//������뼯��		
		if(insert==E)continue;
		for(int i=0;i<exprList.size();++i){//�������еı��ʽ
			if(insert.get(i)){//���ʽi��Ҫ����
				//�����
				InterInst*newInst=exprList[i].genInst(symtab,dfg);//��������ָ��
				list<InterInst*>&insts=inst->block->insts;//ָ�����ڻ������ָ������
				//��block->insts�ڣ���newInst���뵽inst֮ǰ
				insts.insert(find(insts.begin(),insts.end(),inst),newInst);
				// printf("����");
				// newInst->toString();
				// printf("��");
				// inst->toString();
				// printf("֮ǰ\n");
			}
		}
	}
	//������ȫ�����뵽Entry��
	for(int i=0;i<exprList.size();++i){//�������еı��ʽ
		InterInst*decInst=exprList[i].genDec(dfg);//��������ָ��
		if(!decInst)continue;//û�����ɲ���㣬��������
		//declarPoint[i]->insts.push_front(decInst);//���������㵽���֧��ڵ���ײ�
		dfg->blocks[0]->insts.push_back(decInst);//���������㵽Entry��β��
		//dfg->blocks[1]->insts.push_front(decInst);//���������㵽����Entry��Ŀ��ײ�
		// printf("����");
		// decInst->toString();
		//printf("��");
		//declarPoint[i]->toString();
	}
	for(list<InterInst*>::iterator i=optCode.begin();i!=optCode.end();++i){
		InterInst*inst=*i;

		//x+y �� e_use(B) & (~latest[B] | used[B].out)���滻x+y <= t
		Set replace=inst->e_use & (~inst->info.latest | inst->info.used.out);//�����滻����

		if(replace!=E){
			// printf("�滻");
			// inst->toString();
			// printf(" -> ");
			inst->replace(OP_AS,inst->getResult(),exprList[replace.max()].getNewRs());
			// inst->toString();
		}

		// if((inst->e_use & (~inst->info.latest | inst->info.used.out))!=E){
		// 	Var* rs=inst->getResult();//��ȡ���
		// 	Operator op=inst->getOp();//��ȡ������
		// 	Var*arg1=inst->getArg1();//��ȡ������1
		// 	Var*arg2=inst->getArg2();//��ȡ������2
		// 	if(op>=OP_ADD&&op<=OP_GET&&op!=OP_SET){//���еĿ���ʹ�õı��ʽ
		// 		Expr tmp(rs,op,arg1,arg2);//�������ʽ����
		// 		if(findExpr(tmp)!=-1){//���ʽ�Ѿ�����
		// 			inst->toString();
		// 			printf("  x+y<=t\n");
		// 		}
		// 	}
		// }
	}

}