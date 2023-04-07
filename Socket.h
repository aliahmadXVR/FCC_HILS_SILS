#ifndef Socket_Inc
#define	Socket_Inc
#include "Includes.h"


#define HUB_IP		"192.168.0.6"
#define JSB_SIM_IP	"192.168.0.4"
#define Veronte_IP	"192.168.0.10"

class HUB_Socket 
{
public:

	string Sstream_String (char * Buffer);
	BOOL BindSocket(SOCKET * Sock, sockaddr_in* Socket_Addr);
	BOOL WinSocket (WSADATA* WsData);
	void Init_Address(string Str, int Port, sockaddr_in* Socket_Addr);
	void Init_Address(int Port, sockaddr_in* Socket_Addr);
	BOOL UDP_Send_Buffer(char * Buff, int Length, SOCKET* Sock, sockaddr_in* Socket_Addr );
	BOOL UDP_Send_String(string Str,  SOCKET* Sock, sockaddr_in* Socket_Addr );
	int UDP_Receive_Buffer(char * Buff, int Length,  SOCKET* Sock, sockaddr_in* Socket_Addr);
	BOOL UDP_Receive_String(string Str, SOCKET* Sock, sockaddr_in* Socket_Addr );
	BOOL UDP_CreatSocket(SOCKET* Sock);
	void Initialize_UDP(string Ser_Cli);
	void Closeall();

	BOOL TCP_Creat_Sock (SOCKET* Sock);
	BOOL TCP_Connect_to_Server( SOCKET* Sock, sockaddr_in* Socket_Addr);
	void TCP_Listen_Close( SOCKET* Sock, string LC);
	BOOL TCP_Accep_Client(  SOCKET* Sock_SR, SOCKET* Sock_For_Client, sockaddr_in* Socket_Addr_Cl);
	BOOL TCP_Send_Buffer(char * Buff, int Length, SOCKET* Sock);
	BOOL TCP_Send_String(string Str,  SOCKET* Sock );
	int TCP_Receive_Buffer(char * Buff, int Length, SOCKET* Sock);
	string TCP_Receive_String(char * Buff, SOCKET* Sock);
	void Initialize_TCP(string CS);
	void Initialize_Socket(string TCP_UDP, string SC);
//	void Send_Data_JSB(string Str);
	string Rec_Ack_JSB();
	void Send_Data();

};

#define	MAX_BUFF_Size	1024

#endif

#ifdef	Socket_Def

WSADATA		Win_Soc;

//--------------------------------------Server Setting JSB Sim-----------------------
int Server_Ser_Port = 1138;
int Server_Cli_Port = 1137;

// for Server configuration
string Server_Ser_IP = HUB_IP;
string Server_Cli_IP = JSB_SIM_IP;

SOCKET		Server_Listen_Socket;		// for Server Side
SOCKET		Server_Ser_Sock;			// for Server Side
SOCKET		Server_Cli_Sock;			// for Server Side

sockaddr_in Server_Ser_Addr;		// for Server Side
sockaddr_in Server_Cli_Addr;		// for Server Side


//--------------------------------------Client Setting JSB Sim-----------------------
string Client_Ser_IP = JSB_SIM_IP;
string Client_Cli_IP = HUB_IP;

int Client_Ser_Port = 1137;
int Client_Cli_Port = 1138;

SOCKET Client_Ser_Sock;				// for client Side
SOCKET Client_Cli_Sock;				// for client Side

sockaddr_in Client_Ser_Addr;		// for client Side
sockaddr_in Client_Cli_Addr;		// for client Side


//--------------------------------------Veronte Setting-----------------------
SOCKET Veronte_HUB_Sock;				// for client Side
SOCKET HUB_Veronte_Sock;				// for client Side

sockaddr_in Veronte_HUB_Addr;		// for client Side
sockaddr_in HUB_Veronte_Addr;		// for client Side

int Veronte_HUB_Port = 54001;
int HUB_Veronte_Port = 54000;

#endif
