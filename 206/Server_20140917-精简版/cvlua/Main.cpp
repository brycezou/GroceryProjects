//加载必须的头文件
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <windows.h>
#include "cvlua.hpp"

//错误处理函数
LONG WINAPI MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionPtrs)  
{  
	//输出信息
	printf("Unexpected Error!\n"); 
	exit(-1); //退出
	return EXCEPTION_EXECUTE_HANDLER;   
}   

int main(int argc, char *argv[])
{
	//设置错误处理函数
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);  
	__try
	{
		char *init_file = "cvinit.lua";  //脚本文件名称
		char *main_func = "main()"; //需要执行的函数名称

		if (argc >= 2)  //如果参数个数大于等于2
			init_file = argv[1];	//第一个参数为脚本文件名
		if (argc >= 3)  //如果参数个数大于等于3
			main_func = argv[2]; //第二个参数为需要执行的函数名称
		lua_State *L = engine_open(init_file);//加载脚本文件cvinit.lua

		ShowCursor(FALSE); //不要显示鼠标
		while (1)
			engine_eval(L, main_func);			//循环执行脚本文件中的main()函数
		return 0;
	}
	__finally{}
}