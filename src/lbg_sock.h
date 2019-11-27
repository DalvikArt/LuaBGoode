
#ifndef LBG_SOCK
#define LBG_SOCK

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>

typedef struct _Socket
{
	int Valid;
	SOCKET Socket;
} Socket;

#endif //_WIN32

#ifdef __linux__

typedef struct _Socket
{
	int fdSocket;
} Socket;

#endif //__linux__

Socket NewSocket(int port);
int Listen(Socket sock);
Socket AcceptClient(Socket serverSock);

#endif //LBG_SOCK
