
#ifndef LBG_SOCK
#define LBG_SOCK

#ifdef _WIN32

#include <Windows.h>
#include <winsock.h>
#include <ws2def.h>
#include <ws2tcpip.h>

typedef struct _Socket
{
	int Valid;
	SOCKET ListenSocket;
} Socket;

#endif //_WIN32

#ifdef __linux__

typedef struct _Socket
{
	int fdSocket;
} Socket;

#endif //__linux__

Socket NewSock(int port);

#endif //LBG_SOCK
