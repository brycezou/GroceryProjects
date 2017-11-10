#include "IttSelectServer.h"


int main(int argc, char* argv[])
{
    WSAData wsaData;
	int nCode;
    if ((nCode = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) 
	{
		cout << "WSAStartup error " << nCode << endl;
        return -1;
    }
    IttMainRoutine(SERVER_PORT, 20);
    WSACleanup();
    return 0;
} 