#include <Winsock2.h> 
#include <iostream>
#include <vector>
using namespace std;


#define SERVER_PORT			10000
#define RECV_RUFF_SIZE	10240


// 当前连接客户的数据结构
struct IttConnClient
{
	SOCKET hSocket;
	int nBytes;
    char Buffer[RECV_RUFF_SIZE];
    IttConnClient(SOCKET socket) : hSocket(socket), nBytes(0){}
};
typedef vector<IttConnClient*> ClientList;

// 返回一个监听套接字并进入监听状态
SOCKET IttBindListen(int nPort, int nQueueLength);

// 将clients中接收缓冲区未满的套接字句柄放入fdRead中去
void IttResetFdSet(	fd_set& fdRead, fd_set& fdWrite, fd_set& fdExcept, 
								SOCKET fdListen, ClientList& clients );

// 检查是否有新的客户连接
int IttCheckAccept(	fd_set& fdRead, fd_set& fdExcept, 
								SOCKET fdListen, ClientList& clients );

// 接收数据
bool IttReadData(IttConnClient* pConn);

// 检查当前所有客户连接，看看它们是否可读（recv）或者发生I/O错误
void IttReadFromClient(fd_set& fdRead, fd_set& fdExcept, ClientList& clients );

// select就绪通告I/O模型服务器的主体函数
void IttMainRoutine(int nPort, int nQueueLength);
