#include "lbg_sock.h"

#include <stdio.h>
#include <string.h>

#ifdef _WIN32

#pragma comment(lib, "Ws2_32.lib")

int WinsockInitialized = 0;

Socket NewSocket(int port)
{
	Socket newSock;
	newSock.Valid = 0;

	int iResult;

	// initialize winsock
	if (!WinsockInitialized)
	{
		WSADATA wsaData;
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

		if (iResult != 0)
		{
			WSACleanup();
			printf("WSAStartup() failed! %d\n", iResult);
			return newSock;
		}
	}
	
	char strPort[16];
	_itoa(port, strPort, 10);

	struct addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	struct addrinfo* pResult;

	iResult = getaddrinfo(NULL, strPort, &hints, &pResult);

	if (iResult != 0)
	{
		WSACleanup();
		printf("getaddrinfo() failed! %d\n", iResult);
		return newSock;
	}

	newSock.Socket = socket(pResult->ai_family, pResult->ai_socktype, pResult->ai_protocol);

	if (newSock.Socket == INVALID_SOCKET)
	{
		WSACleanup();
		printf("socket() failed! %d\n", iResult);
		return newSock;
	}

	iResult = bind(newSock.Socket, pResult->ai_addr, pResult->ai_addrlen);

	if (iResult == SOCKET_ERROR)
	{
		freeaddrinfo(pResult);
		closesocket(newSock.Socket);
		WSACleanup();
		printf("bind() failed! %d\n", iResult);
		return newSock;
	}

	freeaddrinfo(pResult);

	newSock.Valid = 1;
	return newSock;
}

int Listen(Socket sock)
{
	if (listen(sock.Socket, SOMAXCONN) == SOCKET_ERROR) {
		printf("listen() failed with error: %ld\n", WSAGetLastError());
		closesocket(sock.Socket);
		WSACleanup();
		return 0;
	}

	return 1;
}

Socket AcceptClient(Socket serverSock)
{
	Socket clientSocket;
	clientSocket.Valid = 0;

	clientSocket.Socket = accept(serverSock.Socket, NULL, NULL);

	if (clientSocket.Socket == INVALID_SOCKET)
	{
		printf("accept() failed: %d\n", WSAGetLastError());
		closesocket(serverSock.Socket);
		WSACleanup();
	}
	else
		clientSocket.Valid = 1;

	return clientSocket;
}

#endif

#ifdef __linux__

#endif
