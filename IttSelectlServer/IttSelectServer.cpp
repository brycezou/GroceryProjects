#include "IttSelectServer.h"

#pragma comment (lib, "Ws2_32.lib")


// ����һ�������׽��ֲ��������״̬
SOCKET IttBindListen(int nPort, int nQueueLength)
{
    // ����һ�������׽���
    SOCKET sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd == INVALID_SOCKET)
	{
        cout << "socket error " << WSAGetLastError() <<endl;
        return INVALID_SOCKET;
    }
    // ��䱾���׽��ֵ�ַ
    // ����ʹ����ͨ���ַINADDR_ANY����Ȼ����Ҳ����ָ��һ�������
	// ����IP��ַ������ʹ��ͨ���ַ�Ļ������ǿ��Խ���������������ӿ�
	// ��������������ڴ��ж�������ķ�������˵�����Լ򻯷������ı�̡�
    sockaddr_in saListen;
    saListen.sin_family = AF_INET;
    saListen.sin_addr.s_addr = htonl(INADDR_ANY);
    saListen.sin_port = htons(nPort);
    // ����bind�ѱ����׽��ֵ�ַ�󶨵������׽���
    if(bind(sd, (sockaddr*)&saListen, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
        cout << "bind error " << WSAGetLastError() <<endl;
        closesocket(sd);
        return INVALID_SOCKET;
    }
    // ��ʼ����
    if(listen(sd, nQueueLength) == SOCKET_ERROR)
	{
        cout << "listen error " << WSAGetLastError() <<endl;
        closesocket(sd);
        return INVALID_SOCKET;
    }
    return sd;
}

// ��clients�н��ջ�����δ�����׽��־������fdRead��ȥ
void IttResetFdSet(	fd_set& fdRead, fd_set& fdWrite, fd_set& fdExcept, 
								SOCKET fdListen, ClientList& clients ) 
{
    // ������ո���fd_set��
    FD_ZERO(&fdRead);
    FD_ZERO(&fdWrite);
    FD_ZERO(&fdExcept);
    // �����׽���ÿ�ζ�������fdRead��Ҳ����˵ÿ�ε���select����ȥ���
	// �Ƿ����µ���������
    FD_SET(fdListen, &fdRead);
    FD_SET(fdListen, &fdExcept);

    for(ClientList::const_iterator it = clients.begin(); it != clients.end(); it++) 
	{
        IttConnClient* pConn = *it;
        // �ͻ����ӵĻ��������пռ䣬���Լ����������ݣ�����Ҫ�����Ӧ
		// ���׽��־������fdRead��ȥ��
        if(pConn->nBytes < RECV_RUFF_SIZE) 
		{
            FD_SET(pConn->hSocket, &fdRead);
        }
        // ÿ�����ӵ��׽��־������Ҫ�ŵ�fdExcept���Ա�select�ܹ������I/O����
        FD_SET(pConn->hSocket, &fdExcept);
    }
}

// ����Ƿ����µĿͻ�����
int IttCheckAccept(	fd_set& fdRead, fd_set& fdExcept, 
								SOCKET fdListen, ClientList& clients ) 
{
    int lastErr = 0;
    // ���ȼ���Ƿ�������
    if(FD_ISSET(fdListen, &fdExcept))
	{
        int errlen = sizeof(lastErr);
        getsockopt(fdListen, SOL_SOCKET, SO_ERROR, (char*)&lastErr, &errlen);
        cout << "I/O error " << lastErr << endl;
        return SOCKET_ERROR;
    }
    // ���fdRead���Ƿ�����˼����׽��֣�����ǵĻ���֤�����µ�����
	// ���󣬿��Ե���accept��
    if(FD_ISSET(fdListen, &fdRead)) 
	{
        // ����fd_set�д�С���ƣ����ΪFD_SETSIZE�������Ե����пͻ���
		// �Ӵﵽ�������ʱ�����ٽ�����������
        if(clients.size() >= FD_SETSIZE - 1) 
		{
			cout << "There are too many clients connected to accept any one new ! " << endl;
            return 0;
        }
        // ����accept�����ܿͻ�����
        sockaddr_in saRemote;
        int nSize = sizeof(sockaddr_in);
        SOCKET sd = accept(fdListen, (sockaddr*)&saRemote, &nSize);
        lastErr = WSAGetLastError();
        // Ϊ�˳���Ľ�׳�ԣ����WSAEWOULDBLOCK����
        if(sd == INVALID_SOCKET && lastErr != WSAEWOULDBLOCK)
		{ 
            cout << "accept error" << lastErr << endl;
            return SOCKET_ERROR;
        }
        if(sd != INVALID_SOCKET)
		{
            // ��ȡ���µĿͻ������׽��־������Ҫ������Ϊ������ģʽ��
			// �Ա����ʹ��select������
            u_long nNoBlock = 1;
            if(ioctlsocket(fdListen, FIONBIO, &nNoBlock) == SOCKET_ERROR)
			{
                cout <<"ioctlsocket error " << WSAGetLastError() << endl;
                return SOCKET_ERROR;
            }
            // Ϊ�µĿͻ����Ӵ���һ��IttConnClient���󣬲��Ҽ��뵽clients��ȥ��
            clients.push_back(new IttConnClient(sd));
			cout<<"new client !"<<endl;
        }
    }
    return 0;
}

// ��鵱ǰ���пͻ����ӣ����������Ƿ�ɶ���recv�����߷���I/O����
void IttReadFromClient(	fd_set& fdRead, fd_set& fdExcept, ClientList& clients ) 
{
    ClientList::iterator it = clients.begin();
    while(it != clients.end()) 
	{
        IttConnClient* pConn = *it;
        bool bOK = true;
        // ��鵱ǰ�����Ƿ���I/O����
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
            // ��鵱ǰ�����Ƿ�ɶ�
            if(FD_ISSET(pConn->hSocket, &fdRead)) 
			{
                bOK = IttReadData(pConn);
            }
        }
        // �����˴��󣬹ر��׽��ֲ������Ӧ��IttConnClient�����clients���Ƴ�
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

// select����ͨ��I/Oģ�ͷ����������庯��
void IttMainRoutine(int nPort, int nQueueLength)
{
    // ��ȡ�����׽���
    SOCKET fdListen = IttBindListen(nPort, nQueueLength);
    if(fdListen == INVALID_SOCKET) 
        return;
    // �Ѽ����׽�����Ϊ������ģʽ
    u_long nNoBlock = 1;
    if(ioctlsocket(fdListen, FIONBIO, &nNoBlock) == SOCKET_ERROR) 
	{
        cout <<"ioctlsocket error " << WSAGetLastError() << endl;
        return;
    }
	cout<<"listening..."<<endl;
	// ����clients�����ڱ��浱ǰ���пͻ�����
    ClientList clients;
    fd_set fdRead, fdWrite, fdExcept;
    while(true)
    {
        // ��clients�н��ջ�����δ�����׽��־������fdRead��ȥ��
        IttResetFdSet(fdRead, fdWrite, fdExcept, fdListen, clients);
        // ����select���ȴ��������׽���I/O����
        if(select(0, &fdRead, &fdWrite, &fdExcept, NULL) <= 0)
		{
            cout << "select error " << WSAGetLastError() <<endl;
            break;
        }
        // ����Ƿ����µĿͻ���������
        if(IttCheckAccept(fdRead, fdExcept, fdListen, clients) == SOCKET_ERROR) 
		{
            break;
        }
        // ��ȡ����
        IttReadFromClient(fdRead, fdExcept, clients);
    }
    // �ͷ���Դ
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
	�ɸ���ʵ�������д�˺���������
**********************************************************************/
// ��������
bool IttReadData(IttConnClient* pConn) 
{
    // pConn->Buffer + pConn->nBytes��ʾ������Buffer���ÿռ�Ŀ�ʼλ��
    // RECV_RUFF_SIZE - pConn->nBytes��ʾ������Buffer���ÿռ�Ĵ�С
    int nRet = recv(pConn->hSocket, pConn->Buffer + pConn->nBytes, RECV_RUFF_SIZE - pConn->nBytes, 0);
    if(nRet > 0) 
	{
        pConn->nBytes += nRet;
		pConn->Buffer[pConn->nBytes] = '\0';
		cout<<pConn->Buffer<<endl;
        return true;
    }
    // recv����0������Է��ر������ӡ�
    else if(nRet == 0) 
	{
        cout<<"Connection closed by peer."<<endl;
        return false;
    }
    // �����˴���Ϊ�˳���Ľ�׳�ԣ����WSAEWOULDBLOCK����
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