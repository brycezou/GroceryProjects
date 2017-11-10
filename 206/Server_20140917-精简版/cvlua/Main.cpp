//���ر����ͷ�ļ�
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <windows.h>
#include "cvlua.hpp"

//��������
LONG WINAPI MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionPtrs)  
{  
	//�����Ϣ
	printf("Unexpected Error!\n"); 
	exit(-1); //�˳�
	return EXCEPTION_EXECUTE_HANDLER;   
}   

int main(int argc, char *argv[])
{
	//���ô�������
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);  
	__try
	{
		char *init_file = "cvinit.lua";  //�ű��ļ�����
		char *main_func = "main()"; //��Ҫִ�еĺ�������

		if (argc >= 2)  //��������������ڵ���2
			init_file = argv[1];	//��һ������Ϊ�ű��ļ���
		if (argc >= 3)  //��������������ڵ���3
			main_func = argv[2]; //�ڶ�������Ϊ��Ҫִ�еĺ�������
		lua_State *L = engine_open(init_file);//���ؽű��ļ�cvinit.lua

		ShowCursor(FALSE); //��Ҫ��ʾ���
		while (1)
			engine_eval(L, main_func);			//ѭ��ִ�нű��ļ��е�main()����
		return 0;
	}
	__finally{}
}