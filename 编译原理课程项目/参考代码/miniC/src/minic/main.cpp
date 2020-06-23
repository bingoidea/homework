#include "compiler.h"
#include "error.h"
#include<iostream>
#include<cstring>

/*
	�����ʽ��compile Դ�ļ� [ѡ��]
	ѡ�
		-ch					#��ʾ�ļ��ַ�
		-to				    #��ʾ�ʷ��Ǻ�
		-sy				    #��ʾ���ű���Ϣ
		-mc						#��ʾ�м����
		-h						#��ʾ������Ϣ
*/
int main(int argc,char *argv[])
{
	vector<char*>srcfiles;//Դ�ļ�
	if(argc>1){//����1������
		for(int i=1;i<argc-1;i++){//ȡ���һ������֮ǰ�Ĳ���
			srcfiles.push_back(argv[i]);
		}
		char*opt=argv[argc-1];//���һ������
		if (!strcmp(opt,"-h"))Args::showHelp=true;
		else if(!strcmp(opt,"-to"))Args::showToken=true;
		else if(!strcmp(opt,"-sy"))Args::showSym=true;
		else if(!strcmp(opt,"-mc"))Args::showmc=true;
		else if(!strcmp(opt,"-ch"))Args::showChar=true;
		else srcfiles.push_back(opt);
	}
	if(Args::showHelp){
		cout<<
					"�����ʽ��minic Դ�ļ� [ѡ��]\n"
					"ѡ�\n"
					"\t-ch\t\t#��ʾ�ļ��ַ�\n"
					"\t-to\t\t#��ʾ�ʷ��Ǻ�\n"
					"\t-sy\t\t#��ʾ���ű���Ϣ\n"
					"\t-mc\t\t#��ʾ�м����\n"
					"\t-h\t\t#��ʾ������Ϣ\n"
				;
	}
	else if(srcfiles.size()){//����Դ�ļ�
		Compiler compiler;
		for(int i=0;i<srcfiles.size();i++){
			compiler.compile(srcfiles[i]);
		}
		int error=Error::getErrorNum();
		int warn=Error::getWarnNum();
		cout<<"������ɣ�����="<<error<<",����="<<warn<<"."<<endl;
	}
	else
		cout<<"�����ʽ����(ʹ��-hѡ��鿴����)"<<endl;
	return 0;
}
