#include "IttSelectServer.h"

#pragma comment (lib, "Ws2_32.lib")


// 返回一个监听套接字并进入监听状态
SOCKET IttBindListen(int nPort, int nQueueLength)
{
    // 创建一个监听套接字
    SOCKET sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd == INVALID_SOCKET)
	{
        cout << "socket error " << WSAGetLastError() <<endl;
        return INVALID_SOCKET;
    }
    // 填充本地套接字地址
    // 这里使用了通配地址INADDR_ANY。当然我们也可以指明一个具体的
	// 本地IP地址，但是使用通配地址的话，我们可以接受来自所有网络接口
	// 的连接请求。这对于带有多个网卡的服务器来说，可以简化服务器的编程。
    sockaddr_in saListen;
    saListen.sin_family = AF_INET;
    saListen.sin_addr.s_addr = htonl(INADDR_ANY);
    saListen.sin_port = htons(nPort);
    // 调用bind把本地套接字地址绑定到监听套接字
    if(bind(sd, (sockaddr*)&saListen, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
        cout << "bind error " << WSAGetLastError() <<endl;
        closesocket(sd);
        return INVALID_SOCKET;
    }
    // 开始监听
    if(listen(sd, nQueueLength) == SOCKET_ERROR)
	{
        cout << "listen error " << WSAGetLastError() <<endl;
        closesocket(sd);
        return INVALID_SOCKET;
    }
    return sd;
}

// 将clients中接收缓冲区未满的套接字句柄放入fdRead中去
void IttResetFdSet(	fd_set& fdRead, fd_set& fdWrite, fd_set& fdExcept, 
								SOCKET fdListen, ClientList& clients ) 
{
    // 首先清空各个fd_set。
    FD_ZERO(&fdRead);
    FD_ZERO(&fdWrite);
    FD_ZERO(&fdExcept);
    // 监听套接字每次都被放入fdRead，也就是说每次调用select都会去检测
	// 是否有新的连接请求。
    FD_SET(fdListen, &fdRead);
    FD_SET(fdListen, &fdExcept);

    for(ClientList::const_iterator it = clients.begin(); it != clients.end(); it++) 
	{
        IttConnClient* pConn = *it;
        // 客户连接的缓冲区还有空间，可以继续接收数据，就需要把其对应
		// 的套接字句柄放入fdRead中去。
        if(pConn->nBytes < RECV_RUFF_SIZE) 
		{
            FD_SET(pConn->hSocket, &fdRead);
        }
        // 每个连接的套接字句柄都需要放到fdExcept，以便select能够检测其I/O错误
        FD_SET(pConn->hSocket, &fdExcept);
    }
}

// 检查是否有新的客户连接
int IttCheckAccept(	fd_set& fdRead, fd_set& fdExcept, 
								SOCKET fdListen, ClientList& clients ) 
{
    int lastErr = 0;
    // 首先检查是否发生错误
    if(FD_ISSET(fdListen, &fdExcept))
	{
        int errlen = sizeof(lastErr);
        getsockopt(fdListen, SOL_SOCKET, SO_ERROR, (char*)&lastErr, &errlen);
        cout << "I/O error " << lastErr << endl;
        return SOCKET_ERROR;
    }
    // 检查fdRead中是否包含了监听套接字，如果是的话则证明有新的连接
	// 请求，可以调用accept。
    if(FD_ISSET(fdListen, &fdRead)) 
	{
        // 由于fd_set有大小限制（最多为FD_SETSIZE），所以当已有客户连
		// 接达到这个限制时，不再接收连接请求。
        if(clients.size() >= FD_SETSIZE - 1) 
		{
			cout << "There are too many clients connected to accept any one new ! " << endl;
            return 0;
        }
        // 调用accept来接受客户连接
        sockaddr_in saRemote;
        int nSize = sizeof(sockaddr_in);
        SOCKET sd = accept(fdListen, (sockaddr*)&saRemote, &nSize);
        lastErr = WSAGetLastError();
        // 为了程序的健壮性，检查WSAEWOULDBLOCK错误
        if(sd == INVALID_SOCKET && lastErr != WSAEWOULDBLOCK)
		{ 
            cout << "accept error" << lastErr << endl;
            return SOCKET_ERROR;
        }
        if(sd != INVALID_SOCKET)
		{
            // 获取了新的客户连接套接字句柄后，需要把它设为非阻塞模式，
			// 以便对其使用select函数。
            u_long nNoBlock = 1;
            if(ioctlsocket(fdListen, FIONBIO, &nNoBlock) == SOCKET_ERROR)
			{
                cout <<"ioctlsocket error " << WSAGetLastError() << endl;
                return SOCKET_ERROR;
            }
            // 为新的客户连接创建一个IttConnClient对象，并且加入到clients中去。
            clients.push_back(new IttConnClient(sd));
			cout<<"new client !"<<endl;
        }
    }
    return 0;
}

// 检查当前所有客户连接，看看它们是否可读（recv）或者发生I/O错误
void IttReadFromClient(	fd_set& fdRead, fd_set& fdExcept, ClientList& clients ) 
{
    ClientList::iterator it = clients.begin();
    while(it != clients.end()) 
	{
        IttConnClient* pConn = *it;
        bool bOK = true;
        // 检查当前连接是否发生I/O错误
        if(FD_ISSET(pConn->hSocket, &fdExcept)) 
		{
            bOK = false;
			int lastErr;
			int errlen = sizeof(lastErr);
			getsockopt(pConn->hSocket, SOL_SOCKET, SO_ERROR, (char*)&lastErr, &errlen);
            cout << "I/O error " << lastErr << endl;
        }
        else 
		{
            // 检查当前连接是否可读
            if(FD_ISSET(pConn->hSocket, &fdRead)) 
			{
                bOK = IttReadData(pConn);
            }
        }
        // 发生了错误，关闭套接字并把其对应的IttConnClient对象从clients中移除
        if(bOK == false) 
		{
            closesocket(pConn->hSocket);
            delete pConn;
            it = clients.erase(it);
        }
        else 
		{
            it++;
        }
    }
}

// select就绪通告I/O模型服务器的主体函数
void IttMainRoutine(int nPort, int nQueueLength)
{
    // 获取监听套接字
    SOCKET fdListen = IttBindListen(nPort, nQueueLength);
    if(fdListen == INVALID_SOCKET) 
        return;
    // 把监听套接字设为非阻塞模式
    u_long nNoBlock = 1;
    if(ioctlsocket(fdListen, FIONBIO, &nNoBlock) == SOCKET_ERROR) 
	{
        cout <<"ioctlsocket error " << WSAGetLastError() << endl;
        return;
    }
	cout<<"listening..."<<endl;
	// 定义clients，用于保存当前所有客户连接
    ClientList clients;
    fd_set fdRead, fdWrite, fdExcept;
    while(true)
    {
        // 将clients中接收缓冲区未满的套接字句柄放入fdRead中去。
        IttResetFdSet(fdRead, fdWrite, fdExcept, fdListen, clients);
        // 调用select，等待就绪的套接字I/O操作
        if(select(0, &fdRead, &fdWrite, &fdExcept, NULL) <= 0)
		{
            cout << "select error " << WSAGetLastError() <<endl;
            break;
        }
        // 检查是否有新的客户连接请求
        if(IttCheckAccept(fdRead, fdExcept, fdListen, clients) == SOCKET_ERROR) 
		{
            break;
        }
        // 读取数据
        IttReadFromClient(fdRead, fdExcept, clients);
    }
    // 释放资源
    for(ClientList::iterator it = clients.begin(); it != clients.end(); it++)
	{
        closesocket((*it)->hSocket);
        delete *it;
    }
	clients.clear();
    if(fdListen != INVALID_SOCKET)
        closesocket(fdListen);
}




/**********************************************************************
	可根据实际情况改写此函数的内容
**********************************************************************/
// 接收数据
bool IttReadData(IttConnClient* pConn) 
{
    // pConn->Buffer + pConn->nBytes表示缓冲区Buffer可用空间的开始位置
    // RECV_RUFF_SIZE - pConn->nBytes表示缓冲区Buffer可用空间的大小
    int nRet = recv(pConn->hSocket, pConn->Buffer + pConn->nBytes, RECV_RUFF_SIZE - pConn->nBytes, 0);
    if(nRet > 0) 
	{
        pConn->nBytes += nRet;
		pConn->Buffer[pConn->nBytes] = '\0';
		cout<<pConn->Buffer<<endl;
        return true;
    }
    // recv返回0，代表对方关闭了连接。
    else if(nRet == 0) 
	{
        cout<<"Connection closed by peer."<<endl;
        return false;
    }
    // 发生了错误。为了程序的健壮性，检查WSAEWOULDBLOCK错误。
    else
	{
        int lastErr = WSAGetLastError();
        if(lastErr == WSAEWOULDBLOCK) 
		{
            return true;
        }
        cout <<"recv error " << lastErr << endl;
        return false;
    }
}