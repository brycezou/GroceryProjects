#include <Winsock2.h> 
#include <iostream>
#include <vector>
using namespace std;


#define SERVER_PORT			10000
#define RECV_RUFF_SIZE	10240


// ��ǰ���ӿͻ������ݽṹ
struct IttConnClient
{
	SOCKET hSocket;
	int nBytes;
    char Buffer[RECV_RUFF_SIZE];
    IttConnClient(SOCKET socket) : hSocket(socket), nBytes(0){}
};
typedef vector<IttConnClient*> ClientList;

// ����һ�������׽��ֲ��������״̬
SOCKET IttBindListen(int nPort, int nQueueLength);

// ��clients�н��ջ�����δ�����׽��־������fdRead��ȥ
void IttResetFdSet(	fd_set& fdRead, fd_set& fdWrite, fd_set& fdExcept, 
								SOCKET fdListen, ClientList& clients );

// ����Ƿ����µĿͻ�����
int IttCheckAccept(	fd_set& fdRead, fd_set& fdExcept, 
								SOCKET fdListen, ClientList& clients );

// ��������
bool IttReadData(IttConnClient* pConn);

// ��鵱ǰ���пͻ����ӣ����������Ƿ�ɶ���recv�����߷���I/O����
void IttReadFromClient(fd_set& fdRead, fd_set& fdExcept, ClientList& clients );

// select����ͨ��I/Oģ�ͷ����������庯��
void IttMainRoutine(int nPort, int nQueueLength);
