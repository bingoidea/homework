#pragma once
#include "common.h"
#include <ext/hash_map>
using namespace __gnu_cxx;
/*******************************************************************************
                                   ɨ����
*******************************************************************************/

class Scanner
{
	//�ļ�ָ��
	char*fileName;//�ļ���
	FILE*file;//�ļ�ָ��
	
	//�ڲ�״̬
	static const int BUFLEN=80;//ɨ�軺��������
	char line[BUFLEN];
	int lineLen;//��ǰ�еĳ���
	int readPos;//��ȡ��λ��
	char lastch;//��һ���ַ�����Ҫ�����жϻ���λ��	
	
	//��ȡ״̬
	int lineNum;//��¼�к�
	int colNum;//�к�
	
	//��ʾ�ַ�
	void showChar(char ch);
	
public:

	//�������ʼ��
	Scanner(char* name);
	~Scanner();
	
	//ɨ��
	int scan();//���ڻ��������ַ�ɨ���㷨,�ļ�ɨ����ܺ��Զ��ر��ļ�
	
	//�ⲿ�ӿ�
	char*getFile();//��ȡ�ļ���
	int getLine();//��ȡ�к�
	int getCol();//��ȡ�к�
	
};

/*******************************************************************************
                                   �ؼ��ֱ�
*******************************************************************************/

class Keywords
{
	//hash����
	struct string_hash{
		size_t operator()(const string& str) const{
			return __stl_hash_string(str.c_str());
		}
	};
	hash_map<string, Tag, string_hash> keywords;
public:
	Keywords();//�ؼ����б��ʼ��
	Tag getTag(string name);//�����Ƿ��ǹؼ���
};


/*******************************************************************************
                                   �ʷ�������
*******************************************************************************/

class Lexer
{
	static Keywords keywords;//�ؼ����б�
	
	Scanner &scanner;//ɨ����
	char ch;//������ַ�
	bool scan(char need=0);//ɨ����ƥ��
	
	Token*token;//��¼ɨ��Ĵʷ��Ǻ�
	
public:
	Lexer (Scanner&sc);
	~Lexer();
	Token* tokenize();//�����Զ���ƥ�䣬�ʷ��ǺŽ���
};

