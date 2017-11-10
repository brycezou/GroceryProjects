//���ر�Ҫ��ͷ�ļ�
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "MServer.hpp"
using namespace std;
#include <cvlua.hpp>


static DWORD tid;  //�´������̵߳�ID
static HANDLE hdl; //�´������̵߳ľ��

//�򿪷�����
int start_mserver(lua_State *L)
{
	int argc = lua_gettop(L); //�õ���������
	if (argc != 1) //���������������ȷ
	{
		luaL_error(L, "start_mserver requires 1 argument, %d is given.", argc);
	}

	// Set server_port
	server_port = lua_tonumber(L, 1); //�õ��������˿ں�

	//��ʼ��WinSock
    WSADATA wsaData;
    int iResult;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData); //����WSAStartup
    if (iResult != NO_ERROR)  //�����ʼ��Winsockʧ��
	{
      printf("WSAStartup failed: %d\n", iResult);
      return 1;
    }

	//��ʼ��ָ�����
	cmd_mutex = CreateMutex(NULL, FALSE, NULL); 
	if (!cmd_mutex) //���ָ�������ʼ��ʧ��
	{
		printf("cmd_mutex not create: %d\n", GetLastError());
		exit(0);
	}

	//�����������߳�
	hdl = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)MServer, NULL,0, &tid);
	lua_pushlightuserdata(L, hdl); //���ط������߳̾��
	return 1;
}

//��ȡָ��
int read(lua_State *L)
{
	char *cmd = read_cmd(); //��ָ������ж�ȡָ��
	if (cmd) //���ָ����Ч
	{
		lua_pushstring(L, cmd); //����ָ��
		return 1;
	}
	return 0;
}

//д�����������״̬��Ϣ
int write(lua_State *L)
{
	const char *key = lua_tostring(L, 1); //�õ�״̬������
	const char *val = lua_tostring(L, 2); //�õ�״�����ֵ
	write_statue(key, val); //д�������״̬��Ϣ
	return 0;
}

//��շ���������״̬��Ϣ
int clear(lua_State *L)
{
	clear_statue(); //��շ���������״̬��Ϣ
	return 0;
}

//׷��ָ�ָ�����
int append(lua_State *L)
{
	const char *cmd = lua_tostring(L, 1); //�õ�ָ������
	append_cmd(cmd); //׷��ָ�ָ�����
	return 0;
}

//����ΪLua�ű��ļ�����ʹ�õĿ�
extern "C" int LUA_API luaopen_server(lua_State *L)
{
	struct luaL_reg driver[] = 
	{
		//��һ��Ϊlua�ű��������õĺ�����, �ڶ���Ϊ���غ�����
		//��ͬ
		{"start_mserver", start_mserver},
		{"read", read},
		{"append", append},
		{"write", write},
		{"clear", clear},
		{NULL, NULL}
	};
	luaL_register(L, "server", driver);  //ע���
	fprintf(stderr, "server module is loaded\n");
	return 1;
}