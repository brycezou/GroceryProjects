//包含必要的头文件
#pragma once
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <string>
#include <map>
using namespace std;
#include <windows.h>


//客户端结构体
struct client
{
	int fd; //客户端套接字
	char *data; //客户端数据
	int data_len; //客户端数据长度
};

//声明外部变量
extern map<int, client> clients;	//存储客户端的映射表
extern deque< pair<int,string> > cmds; //指令队列
extern map<string, string> statue; //服务器状态信息表
extern HANDLE cmd_mutex; //指令互斥锁句柄
extern int cmd_id; //指令ID
extern string current_cmd; //当前指令
extern int current_id; //当前指令的ID

extern int server_port; //服务器端口号

int WINAPI MServer(); //服务器初始化函数
char *read_cmd(); //读取指令函数
void append_cmd(const char *cmd); //追加指令函数
void write_statue(const char *key, const char *val); //写入服务器状态信息
void clear_statue(); //清理服务器状态信息