#include "stdafx.h"
#define Socket_Def
#include "Socket.h"

string HUB_Socket::Sstream_String (char * Buffer)
{
	unsigned int Index = 0;
	std::ostringstream ss;
	do
	{
		if(Index < MAX_BUFF_Size)	ss<< Buffer[Index];
		else	return "\n";
	}while(Buffer[Index++] != 0x0a);

	std::string s(ss.str());
	return s;
}

BOOL HUB_Socket::BindSocket(SOCKET * Sock, sockaddr_in* Socket_Addr)
{
	if (bind(*Sock, (sockaddr*)Socket_Addr, sizeof(*Socket_Addr)) == SOCKET_ERROR)
	{
		cout << "Can't bind socket! " << WSAGetLastError() << endl;
		
		WSACleanup();
		return 0;
	}
	return 1;
}

BOOL HUB_Socket::WinSocket (WSADATA* WsData)
{
	WORD version = MAKEWORD(2, 2);

	int wsOk = WSAStartup(version,  WsData);

	if (wsOk != 0)
	{
		cout << "Can't start Winsock! " << wsOk << endl;
		return 0;
	}
	return 1;
}

void HUB_Socket::Init_Address(string Str, int Port, sockaddr_in* Socket_Addr)
{
	Socket_Addr->sin_family = AF_INET; 
	Socket_Addr->sin_port = htons(Port);
	inet_pton(AF_INET,Str.c_str(), (PVOID) &(Socket_Addr->sin_addr));	
//	inet_pton(AF_INET,Str.c_str(), (PVOID) &(Socket_Addr->sin_addr.S_un.S_addr));	


}

void HUB_Socket::Init_Address(int Port, sockaddr_in* Socket_Addr)
{
	Socket_Addr->sin_addr.S_un.S_addr = INADDR_ANY; 
	Socket_Addr->sin_family = AF_INET; 
	Socket_Addr->sin_port = htons(Port); 
}


void HUB_Socket::Closeall()
{
	closesocket(Client_Ser_Sock);
	closesocket(Client_Cli_Sock);
	closesocket(Server_Listen_Socket);
	closesocket(Server_Ser_Sock);
	closesocket(Server_Cli_Sock);
	WSACleanup();
}


BOOL HUB_Socket::UDP_Send_Buffer(char * Buff, int Length, SOCKET* Sock, sockaddr_in* Socket_Addr )
{
	
//	int Socket_Addr_Length = sizeof(*Socket_Addr);

	int sendOk = sendto(*Sock, Buff, Length, 0, (sockaddr*)Socket_Addr, sizeof(*Socket_Addr));
	
//	int sendOk = sendto(Server_Sock, Buff,Length, 0, (sockaddr*)&Client_Addr, sizeof(Client_Addr));

	if (sendOk == SOCKET_ERROR)
	{
		cout << "Error in sending" << WSAGetLastError() << endl;
		return 0;
	}
	return 1;
}

BOOL HUB_Socket::UDP_Send_String(string Str,  SOCKET* Sock, sockaddr_in* Socket_Addr )
{
	int sendOk = sendto(*Sock, Str.c_str(),Str.size() + 1, 0, (sockaddr*)Socket_Addr, sizeof(*Socket_Addr));
	if (sendOk == SOCKET_ERROR)
	{
		cout << "Error in sending" << WSAGetLastError() << endl;
		return 0;
	}
	return 1;
}


int HUB_Socket::UDP_Receive_Buffer(char * Buff, int Length,  SOCKET* Sock, sockaddr_in* Socket_Addr)
{
	
	int SocketLength = sizeof(*Socket_Addr); // The size of the Client information

	ZeroMemory(Socket_Addr, SocketLength); // Clear the Client structure
	ZeroMemory(Buff, Length); // Clear the receive buffer

	
	int bytesIn = recvfrom(*Sock, Buff, MAX_BUFF_Size, 0, (sockaddr*)Socket_Addr, &SocketLength);

	if (bytesIn == SOCKET_ERROR)
	{
		cout << "Error receiving " << WSAGetLastError() << endl;
		return 0;
	}
	return bytesIn;
}

BOOL HUB_Socket::UDP_Receive_String(string Str, SOCKET* Sock, sockaddr_in* Socket_Addr )
{
	/*	int clientLength = sizeof(Client); // The size of the Client information
		char Var;
		ZeroMemory(&Client, clientLength); // Clear the Client structure
		ZeroMemory(Buff, sizeof(Buff)); // Clear the receive buffer

		int bytesIn = recvfrom(In, &Var, 1, 0, (sockaddr*)&Socket, &clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			cout << "Error receiving from Client " << WSAGetLastError() << endl;
			return 0;
		}*/
		return 1;
}


BOOL HUB_Socket::UDP_CreatSocket(SOCKET* Sock)
{
	*Sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (*Sock == INVALID_SOCKET)
	{
		//cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		cout << "Can't start Winsock! " << WSAGetLastError() ;
		
		WSACleanup();
		return 0;
	}
	return 1;
}


//void Initialize_UDP(string Ser_IP, string Cli_IP, int Ser_Port, int Cli_Port, string Str, SOCKET* Ser_Sock, SOCKET* Cli_Sock)
void HUB_Socket::Initialize_UDP(string Ser_Cli)
{

	WinSocket(&Win_Soc);

	if(strcmp(Ser_Cli.c_str(),"Server") == 0)
	{
		Init_Address(HUB_IP, Veronte_HUB_Port, &Veronte_HUB_Addr);
		UDP_CreatSocket(&Veronte_HUB_Sock);
		BindSocket(&Veronte_HUB_Sock, &Veronte_HUB_Addr);
	}
	else
	{
		Init_Address(Veronte_IP, HUB_Veronte_Port, &HUB_Veronte_Addr);
		UDP_CreatSocket(&HUB_Veronte_Sock);
//		BindSocket(&HUB_Veronte_Sock, &HUB_Veronte_Addr);

	}
	/*
	
	if(strcmp(Ser_Cli.c_str(),"Server") == 0)
	{
		Init_Address(Server_Ser_IP, Server_Ser_Port, &Server_Ser_Addr);
		Init_Address(Server_Cli_IP, Server_Cli_Port, &Client_Ser_Addr);
		UDP_CreatSocket(&Server_Ser_Sock);
		BindSocket(&Server_Ser_Sock, &Server_Ser_Addr);
	}
	else
	{
		Init_Address(Client_Ser_IP, Client_Ser_Port, &Client_Ser_Addr);
		Init_Address(Client_Cli_IP, Client_Cli_Port, &Client_Cli_Addr);
		UDP_CreatSocket(&Client_Cli_Sock);
		BindSocket(&Client_Cli_Sock, &Client_Cli_Addr);
	}
	*/

}


BOOL HUB_Socket::TCP_Creat_Sock (SOCKET* Sock)
{
	// Create socket
	*Sock = socket(AF_INET, SOCK_STREAM, 0);
	if (*Sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	return 1;
}


BOOL HUB_Socket::TCP_Connect_to_Server( SOCKET* Sock, sockaddr_in* Socket_Addr)
{
	int connResult = connect(*Sock, (sockaddr*)Socket_Addr, sizeof(*Socket_Addr));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	return 1;
}

void HUB_Socket::TCP_Listen_Close( SOCKET* Sock, string LC)
{
	if((strcmp(LC.c_str(),"Listen")) == 0)
	{
		listen(*Sock, SOMAXCONN);
	
	}
	else 
	{
		closesocket(*Sock);
	}
	
}
BOOL HUB_Socket::TCP_Accep_Client(  SOCKET* Sock_SR, SOCKET* Sock_For_Client, sockaddr_in* Socket_Addr_Cl)
{
	
	char host[NI_MAXHOST];		// Client's remote name
	char service[NI_MAXSERV];	// Service (i.e. port) the client is connect on

	ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);
	int clientSize = sizeof(*Socket_Addr_Cl);
	
	*Sock_For_Client = accept(*Sock_SR, (sockaddr*)Socket_Addr_Cl, &clientSize);
	
	if (getnameinfo((sockaddr*)Socket_Addr_Cl, sizeof(*Socket_Addr_Cl), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connected on port " << service << endl;
	}
	else
	{
		inet_ntop(AF_INET, &Socket_Addr_Cl->sin_addr, host, NI_MAXHOST);
		cout << host << " connected on port " <<ntohs(Socket_Addr_Cl->sin_port) << endl;
	}
	return 1;
}

BOOL HUB_Socket::TCP_Send_Buffer(char * Buff, int Length, SOCKET* Sock)
{
	int sendResult = send(*Sock, Buff, Length, 0);
	if (sendResult == SOCKET_ERROR)
	{
		cout << "Error in sending" << WSAGetLastError() << endl;
		return 0;
	}
	return 1;
}


BOOL HUB_Socket::TCP_Send_String(string Str,  SOCKET* Sock )
{
	int sendResult = send(*Sock, Str.c_str(), Str.size() + 1, 0);
	if (sendResult == SOCKET_ERROR)
	{
		cout << "Error in sending" << WSAGetLastError() << endl;
		return 0;
	}
	return 1;
}


int HUB_Socket::TCP_Receive_Buffer(char * Buff, int Length, SOCKET* Sock)
{
	ZeroMemory(Buff, Length);
	int bytesReceived = recv(*Sock, Buff, Length, 0);
	if ( bytesReceived == SOCKET_ERROR )
	{
		cerr << "Error in recv TCp Data Buff" << endl;
		return 0;
	}
	return bytesReceived;
}

string HUB_Socket::TCP_Receive_String(char * Buff, SOCKET* Sock)
{
	char Temp;
	int bytesReceived ;
//	char Buff[MAX_BUFF_Size];
	unsigned int Index = 0;

	ZeroMemory(Buff, MAX_BUFF_Size);
	
	do
	{
		
		bytesReceived = recv(*Sock, &Temp, 1, 0);
		if ( bytesReceived > 0 )
			/*if ( bytesReceived == SOCKET_ERROR )
		{
			cerr << "Error in recv TCp Data string" << endl;
			return "\n";
		}*/
		{
			if(Index < MAX_BUFF_Size)
			{
				Buff[Index++] = Temp;
			}
			else	return "\n";
		}
	}while(Temp != 0x0a);

	return (Sstream_String (Buff));
	
}


void HUB_Socket::Initialize_TCP(string CS)
{
	
	WinSocket(&Win_Soc);
	if((strcmp(CS.c_str(),"Server")) == 0)
	{
// Server initialization
		Init_Address(Server_Ser_IP, Server_Ser_Port, &Server_Ser_Addr);
//		Init_Address(Server_Cli_IP, Server_Cli_Port, &Server_Cli_Addr);

		if(	TCP_Creat_Sock(&Server_Listen_Socket) == 0	)	return;

		if(	BindSocket(&Server_Listen_Socket, &Server_Ser_Addr)	==	0	)	return;

		TCP_Listen_Close(&Server_Listen_Socket, "Listen");

		if(	TCP_Accep_Client(&Server_Listen_Socket, &Server_Ser_Sock, &Server_Cli_Addr)	==	0	)	return;

//		TCP_Listen_Close(&Server_Listen_Socket, "Close");

	}
	else
	{
// Client initialization

		if(	TCP_Creat_Sock(&Client_Cli_Sock)	==	0	)	return;

		Init_Address(Client_Ser_IP, Client_Ser_Port, &Client_Ser_Addr);

//		Init_Address(Client_Port, &Client_Addr);

//		if(	BindSocket(&Server_Sock, &Server_Addr)	==	0	)	return;			//	uncomment bind if static port and address is needed 
		
		if(	TCP_Connect_to_Server(&Client_Cli_Sock, &Client_Ser_Addr)	==	0	)	return;
	}
	
}

void HUB_Socket::Initialize_Socket(string TCP_UDP, string SC)
//void Initialize_Socket(string TCP_UDP, string SC)

{

//	string TCP_UDP;
//	string SC;
	if(strcmp(TCP_UDP.c_str(),"UDP") == 0)
	{
		if(strcmp(SC.c_str(),"Server")== 0)
			Initialize_UDP(SC);
		else
			Initialize_UDP(SC);
	}
	else if (strcmp(TCP_UDP.c_str(),"TCP") == 0)
	{
		if(strcmp(SC.c_str(),"Server")== 0)
			Initialize_TCP(SC);
		else
			Initialize_TCP(SC);
	}
	else
	{
		cout << "Invalid Setting" << endl;
	}
}


void HUB_Socket::Send_Data()
{
	//TCP_Send_String("shabbir",&Client_Sock);

	//int Received_Data_Bytes = TCP_Receive_Buffer(char * Buff, int Length, SOCKET* Sock);

/*		char buff[4096];
		//string st= "info\n";
		string st= "help\n";
		string stt= "info\n";


		int temp = 22;
		//send(Client_Sock, st.c_str(), st.size() + 1, 0);
	*/	
/*	
//TCP Server
		while (true)
		{
			ZeroMemory(buff, 4096);
		//	
		//	int bytesReceived;
			int bytesReceived = TCP_Receive_Buffer(buff, 4096, &Server_Ser_Sock);
		
		//	else if (bytesReceived > 0)
			if (bytesReceived > 0)
			{
			cout << string(buff, 0, bytesReceived) << endl;

			// Echo message back to client
			//send(Server_Ser_Sock, buff, 1, 0);
			}
		}
*/

/*
//TCP Client
	//	send(Client_Cli_Sock, buff, 1, 0);
		while (true)
		{
			ZeroMemory(buff, 4096);
			
			//char stt[256];
			 string stt ;
			 
			//int bytesReceived = 2;
			int bytesReceived = TCP_Receive_Buffer(buff, 1024, &Client_Cli_Sock);
			if (bytesReceived > 0)
			{
			//temp = 0;
			
			//fgets(stt, 255,stdin);  
			
			cout << string(buff, 0, bytesReceived) << endl;
			string ss;	
			cout<<"enter msg";
			cin >> ss ;

			//send(Client_Cli_Sock, stt, sizeof(stt), 0);
					send(Client_Cli_Sock, st.c_str(), st.size() + 1, 0);
			//	send(Client_Cli_Sock, stt.c_str(), stt.size() + 1, 0);
				// Echo message back to client
				//	send(Client_Cli_Sock, buff, 1 , 0);
			}
			
			

		//	send(Client_Cli_Sock, st.c_str(), st.size() + 1, 0);
		//	send(Client_Cli_Sock, buff, 4 , 0);
		
		}
*/

/*
// UDP Server
	while (true)
	{
		ZeroMemory(buff, 4096);

		// UDP Server
		int bytesReceived = UDP_Receive_Buffer(buff, 1, &Server_Ser_Sock,&Server_Cli_Addr);
		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv(). Quitting" << endl;
		}

		else if (bytesReceived > 0)
		{
			cout << string(buff, 0, bytesReceived) << endl;
			// Echo message back to client
		//	UDP_Send_Buffer(&st.c_str(),st.length()+1, &Server_Ser_Sock, &Server_Cli_Addr);
		//	send(Server_Ser_Sock, st.c_str(), st.length(), 0);
			//UDP_Send_Buffer(&buff[5],1, &Server_Ser_Sock, &Server_Cli_Addr);
		}
	}
*/

/*
//UDP Client
	UDP_Send_Buffer(buff,1, &Client_Cli_Sock, &Client_Ser_Addr);
	while(true)
	{
		buff[5] = 100;
		int bytesReceived = UDP_Receive_Buffer(buff, 1, &Client_Cli_Sock, &Client_Ser_Addr);
		if (bytesReceived == SOCKET_ERROR)
		{
			cerr << "Error in recv(). Quitting" << endl;
			
		}
		else if (bytesReceived > 0)
		{
			
			cout << string(buff, 0, bytesReceived) << endl;
			// Echo message back to client
			buff[5] = 105;
			UDP_Send_Buffer(&buff[5],1, &Client_Cli_Sock, &Client_Ser_Addr);
		}
	}
*/

}


