#ifndef _CONNECTION_
#define _CONNECTION_

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef __linux__
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#endif
#ifdef __WIN32__
#include <winsock2.h>
#endif

#include <string>
#include <iostream>

using namespace std;

class Connection {
public:
	Connection(short port);

	bool sendMsg(string msg);
	string readLine();
private:
#ifdef __linux__
	int sock;
#endif
#ifdef __WIN32__
	SOCKET sock;
#endif
};

#endif