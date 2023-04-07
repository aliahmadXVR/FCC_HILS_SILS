
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

	WSAData data;
	SOCKET sock;
sockaddr_in hint;