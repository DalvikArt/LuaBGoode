#include "lbg_debuggee.h"

#include "lbg_sock.h"

int WaitForDebugger(int port)
{
	Socket serverSock = NewSocket(port);

	if (!serverSock.Valid)
		return 0;

	if (!Listen(serverSock))
		return 0;

	Socket debuggerSock = AcceptClient(serverSock);

	if (!debuggerSock.Valid)
		return 0;

	return 1;
}