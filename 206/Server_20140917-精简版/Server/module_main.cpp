//加载必要的头文件
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "MServer.hpp"
using namespace std;
#include <cvlua.hpp>


static DWORD tid;  //新创建的线程的ID
static HANDLE hdl; //新创建的线程的句柄

//打开服务器
int start_mserver(lua_State *L)
{
	int argc = lua_gettop(L); //得到参数个数
	if (argc != 1) //如果参数个数不正确
	{
		luaL_error(L, "start_mserver requires 1 argument, %d is given.", argc);
	}

	// Set server_port
	server_port = lua_tonumber(L, 1); //得到服务器端口号

	//初始化WinSock
    WSADATA wsaData;
    int iResult;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData); //调用WSAStartup
    if (iResult != NO_ERROR)  //如果初始化Winsock失败
	{
      printf("WSAStartup failed: %d\n", iResult);
      return 1;
    }

	//初始化指令互斥锁
	cmd_mutex = CreateMutex(NULL, FALSE, NULL); 
	if (!cmd_mutex) //如果指令互斥锁初始化失败
	{
		printf("cmd_mutex not create: %d\n", GetLastError());
		exit(0);
	}

	//创建服务器线程
	hdl = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)MServer, NULL,0, &tid);
	lua_pushlightuserdata(L, hdl); //返回服务器线程句柄
	return 1;
}

//读取指令
int read(lua_State *L)
{
	char *cmd = read_cmd(); //从指令队列中读取指令
	if (cmd) //如果指令有效
	{
		lua_pushstring(L, cmd); //返回指令
		return 1;
	}
	return 0;
}

//写入服务器运行状态信息
int write(lua_State *L)
{
	const char *key = lua_tostring(L, 1); //得到状态参数名
	const char *val = lua_tostring(L, 2); //得到状体参数值
	write_statue(key, val); //写入服务器状态信息
	return 0;
}

//清空服务器运行状态信息
int clear(lua_State *L)
{
	clear_statue(); //清空服务器运行状态信息
	return 0;
}

//追加指令到指令队列
int append(lua_State *L)
{
	const char *cmd = lua_tostring(L, 1); //得到指令内容
	append_cmd(cmd); //追加指令到指令队列
	return 0;
}

//导出为Lua脚本文件可以使用的库
extern "C" int LUA_API luaopen_server(lua_State *L)
{
	struct luaL_reg driver[] = 
	{
		//第一项为lua脚本可以引用的函数名, 第二项为本地函数名
		//下同
		{"start_mserver", start_mserver},
		{"read", read},
		{"append", append},
		{"write", write},
		{"clear", clear},
		{NULL, NULL}
	};
	luaL_register(L, "server", driver);  //注册库
	fprintf(stderr, "server module is loaded\n");
	return 1;
}