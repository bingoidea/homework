#include "compiler.h"
#include "error.h"
#include<iostream>
#include<cstring>

/*
	命令格式：compile 源文件 [选项]
	选项：
		-ch					#显示文件字符
		-to				    #显示词法记号
		-sy				    #显示符号表信息
		-mc						#显示中间代码
		-h						#显示帮助信息
*/
int main(int argc,char *argv[])
{
	vector<char*>srcfiles;//源文件
	if(argc>1){//至少1个参数
		for(int i=1;i<argc-1;i++){//取最后一个参数之前的参数
			srcfiles.push_back(argv[i]);
		}
		char*opt=argv[argc-1];//最后一个参数
		if (!strcmp(opt,"-h"))Args::showHelp=true;
		else if(!strcmp(opt,"-to"))Args::showToken=true;
		else if(!strcmp(opt,"-sy"))Args::showSym=true;
		else if(!strcmp(opt,"-mc"))Args::showmc=true;
		else if(!strcmp(opt,"-ch"))Args::showChar=true;
		else srcfiles.push_back(opt);
	}
	if(Args::showHelp){
		cout<<
					"命令格式：minic 源文件 [选项]\n"
					"选项：\n"
					"\t-ch\t\t#显示文件字符\n"
					"\t-to\t\t#显示词法记号\n"
					"\t-sy\t\t#显示符号表信息\n"
					"\t-mc\t\t#显示中间代码\n"
					"\t-h\t\t#显示帮助信息\n"
				;
	}
	else if(srcfiles.size()){//存在源文件
		Compiler compiler;
		for(int i=0;i<srcfiles.size();i++){
			compiler.compile(srcfiles[i]);
		}
		int error=Error::getErrorNum();
		int warn=Error::getWarnNum();
		cout<<"编译完成：错误="<<error<<",警告="<<warn<<"."<<endl;
	}
	else
		cout<<"命令格式错误！(使用-h选项查看帮助)"<<endl;
	return 0;
}
