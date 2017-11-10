//加载必要的头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

#include <sstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "MServer.hpp"


map<int, client> clients; //存储客户端的映射表
deque< pair<int, string> > cmds;  //指令队列
map<string, string> statue; //服务器状态信息表
HANDLE cmd_mutex; //指令互斥锁句柄
int cmd_id = 0; //指令ID
string current_cmd; //当前指令
int current_id = -1; //当前指令的ID
int server_port = 1400; //服务器端口号

//解析字符串
void handler(client &c){
	string val = "nil\n";
	if (WaitForSingleObject(cmd_mutex, 100) != 0){ //如果等待释放互斥锁失败
		val = "busy waiting for lock\n";
		goto die; //跳转到结束语句
	}
	if (c.data[0] == '?'){	//如果查询状态
		if (strcmp(c.data, "?") == 0){ //如果是查询所有状态
			ostringstream oss;
			oss << "{";
			//将所有状态数据组装成Json格式
			for (map<string,string>::iterator mi = statue.begin(); mi != statue.end(); mi++){
				oss << "\"" << mi->first << "\"" << ":" << "\"" << mi->second + "\"" << ",";
			}
			oss << "}\n";
			val = oss.str(); //将输出流转为字符串
		}else{
			string key = c.data+1; //得到要查询的状态参数名称
			if(statue.count(key) > 0) //如果服务器状态表中存在该状态名称
				val = statue[key]+"\n"; //得到该状态的值
			cerr<<key<<":"<<val<<endl;
		}
		goto end;
	}
	if (c.data[0] == '#'){	//如果查询当前指令
		if (strcmp(c.data, "#") == 0){ //如果查询当前指令的ID
			ostringstream oss;
			oss<<current_id<<endl; //输出当前指令的ID
			val = oss.str(); //转换成字符串
		}else{ //如果根据指令ID查找指令名称
			int cid = atoi(c.data+1); //得到指令的ID
			if (cid == current_id){ //如果查询的是当前指令
				val = current_cmd + "\n"; //得到当前指令名称
				goto end; //跳转到结束语句
			}
			//如果查询的不是当前指令
			for (deque<pair<int, string>>::iterator i = cmds.begin(); i != cmds.end(); i++){
				if(cid == i->first){
					val = i->second + "\n"; //遍历指令队列得到指令名称
					break;
				}
			}
		}
		goto end;
	}
	if (c.data[0] == '-'){ //如果删除指令
		int cid = atoi(c.data+1); //得到指令的ID
		for (deque<pair<int, string>>::iterator i = cmds.begin(); i != cmds.end(); i++){
			if(cid == i->first){ //遍历指令队列找到要删除的指令
				cmds.erase(i);  //从指令队列中删除指令
				break;
			}
		}
		goto end; //跳转到结束语句
	}
	if (c.data[0] == '@'){ //如果是查询指令队列指令
		ostringstream oss;
		oss << "{";
		//将所有指令组装成Json格式
		for (deque<pair<int, string>>::iterator qi = cmds.begin(); qi != cmds.end(); qi++){
			oss << "\"" << qi->first << "\"" << ":" << "\"" << qi->second << "\"" << ",";
		}
		oss << "}\n";
		val = oss.str(); //转换成字符串
		goto end; //跳转到结束语句
	}
	if (c.data_len > 2){ //如果是执行指令
		cmds.push_back(make_pair(cmd_id, string(c.data))); //加入指令队列
		ostringstream oss;
		oss << cmd_id << "\n"; //输出指令的ID
		val = oss.str(); //转换成字符串
		cmd_id++; //指令ID自增
	}
	
end:
	ReleaseMutex(cmd_mutex); //释放互斥锁
die:
	send(c.fd, val.c_str(), val.length(), 0); //向客户端发送数据
	c.data_len = 0; //客户端数据长度清零
	memset(c.data, 0, 1024*1024); //客户端数据存储块清空
}

//服务器初始化函数
int WINAPI MServer(void)
{
	int port = 1400; //端口号
	int server_fd, client_fd; //服务器和客户端套接字
	struct sockaddr_in server_addr, client_addr; //地址结构体
	int server_addr_len, client_addr_len; //地址结构体的大小
	memset(&server_addr, 0, sizeof(struct sockaddr_in)); //地址结构体复位

	//初始化服务器端地址结构体
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	server_fd = socket(AF_INET, SOCK_STREAM, 0); //初始化服务器套接字
	if (server_fd == -1) //如果服务器套接字初始化失败
		exit(-1); //退出程序
	//绑定服务器地址结构体到服务器套接字
	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		exit(-1); //退出程序

	listen(server_fd, 5);  //监听套接字

	fd_set rfds, wfds, efds; //定义读、写和错误事件监听器
	struct timeval tv; //超时时间结构体
	int retval; //多路复用返回值
	while (1){ //无限循环, 一直监听
		FD_ZERO(&rfds); //重置读事件监听器
		FD_ZERO(&wfds); //重置写事件监听器
		FD_ZERO(&efds); //重置错误事件监听器

		int max_fd = server_fd;
		FD_SET(server_fd, &rfds); //将服务器监听套接字设置为读事件监听器
		//将所有客户端套接字设置为读事件和错误事件监听器
		for (map<int, client>::iterator i = clients.begin(); i != clients.end(); i++){
			FD_SET(i->second.fd, &rfds); //将客户端套接字设置为读事件监听器
			FD_SET(i->second.fd, &efds); //将客户端套接字设置为错误事件监听器
			max_fd = i->second.fd > max_fd ? i->second.fd : max_fd;
		}
		tv.tv_sec = 5; //设置超时时间

		retval = select(max_fd + 1, &rfds, &wfds, &efds, &tv); //多路复用等待事件发生
		if (retval == SOCKET_ERROR){//如果多路复用发生错误
			int err = WSAGetLastError(); //得到错误信息
			printf("select error %d\n", err); //输出错误信息
		}else if (retval){//如果多路复用未发生错误
			//printf("Data is ready\n");
			if (FD_ISSET(server_fd, &rfds)){ //如果有客户端请求连接
				client_addr_len = sizeof(client_addr); //得到客户端地址结构体的大小
				//接收客户端连接
				client_fd = accept(server_fd, \
					(struct sockaddr *)&client_addr, \
					&client_addr_len);
				if(client_fd == -1){ //如果连接失败
					int err = WSAGetLastError(); //得到错误信息
					printf("accept error %d\n", err); //输出错误信息
					continue; //进入下一次循环
				}
				//如果客户端连接成功
				struct client c; //客户端连接套接字结构体对象
				c.fd = client_fd; //为套接字赋值
				c.data = (char *)malloc(1024*1024); //为接收数据块分配内存
				c.data_len = 0; //接收数据长度为0
				memset(c.data, 0, 1024*1024); //接收数据块清零
				clients[client_fd] = c; //将该客户端存入客户端映射表
				printf("new connection %d\n", c.fd); //输出信息
			}

			for (map<int, client>::iterator i = clients.begin(); i != clients.end();++i){
				if (FD_ISSET(i->first, &rfds)){ //如果客户端套接字有读事件
					int recv_len = recv(i->first, i->second.data+i->second.data_len, \
						1, 0); //从客户端接收数据
					// client socket close
					if (recv_len == 0){ //如果客户端套接字关闭
						closesocket(i->first); //关闭套接字
						free(i->second.data); //释放数据块
						clients.erase(i); //将该客户从映射表中删除
						break;
					}

					// data recv
					if (recv_len > 0){ //如果接收到了数据
						if (i->second.data[i->second.data_len] == '\n'){ //如果数据接收完毕
							i->second.data[i->second.data_len] == '\0'; //设置字符串的结束符
							char *p = strchr(i->second.data, '\n'); //得到字符串中'\n'首次出现的位置
							if (p) *p = '\0'; //字符串截尾
							handler(i->second); //解析字符串
						}else{ //如果数据还未接受完毕
							i->second.data_len += recv_len; //更新已接收数据长度
						}
					} // end data recv
				}
			}// end for i = clients.begin
		}else{
			;//printf("No data\n");
		}
	}
}

//从指令队列读取指令
char *read_cmd()
{
	char *retval = NULL;
	//等待互斥锁解锁
	WaitForSingleObject(cmd_mutex, INFINITE);

	//remove old cmd
	if (!cmds.empty()){ //如果指令队列非空
		pair<int, string> cmd = cmds.front(); //得到指令队列的第一条指令
		if (current_id == cmd.first)
			cmds.pop_front(); //删除第一条指令
	}

	//read new cmd
	if (!cmds.empty()){ //如果指令队列非空
		pair<int, string> cmd = cmds.front(); //得到指令队列的第一条指令
		retval = strdup(cmd.second.c_str()); //将指令复制
		current_id = cmd.first; //当前指令的ID
		current_cmd = cmd.second; //当前指令的名称
	}else{ //如果指令队列为空
		current_id = -1;
	} 
	ReleaseMutex(cmd_mutex);  //释放互斥锁
	return retval; //返回当前指令
}

//向指令队列追加指令
void append_cmd(const char *cmd)
{
	//等待互斥锁解锁
	WaitForSingleObject(cmd_mutex, INFINITE);
	//向指令队列添加指令
	cmds.push_back(make_pair(cmd_id++, string(cmd)));
	 //释放互斥锁
	ReleaseMutex(cmd_mutex);
}

//写系统状态信息
void write_statue(const char *key, const char *val)
{
	//等待互斥锁解锁
	WaitForSingleObject(cmd_mutex, INFINITE);
	//保存系统状态信息
	statue[key] = val;
	//释放互斥锁
	ReleaseMutex(cmd_mutex);
}

//清除系统状态信息
void clear_statue()
{
	//等待互斥锁解锁
	WaitForSingleObject(cmd_mutex, INFINITE);
	//清除系统状态
	statue.clear();
	//释放互斥锁
	ReleaseMutex(cmd_mutex);
}