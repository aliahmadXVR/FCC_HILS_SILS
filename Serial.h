#ifndef Serial_Inc
#define	Serial_Inc

#include"Includes.h"

#define	TelemetryPort	"COM1"
#define Rx_FRAME_LENGTH_COM1	128
#define Tx_FRAME_LENGTH_COM1	128

class Serial 
{
public:

	void Initialize_Port();
	BOOL Create_Port(LPCSTR Comport_No, HANDLE * hComm, DCB * dcbComm);
	DWORD Read(HANDLE hComm, char * lpBuf, int dwToRead);
	DWORD Write(HANDLE hComm, char * lpBuf, int dwToWrite); 
};

#endif

#ifdef Serial_Def
//HANDLE	hTelemetry;
//DCB		dcbTelemetry;
char lpBuf[100];

HANDLE hCom1;
HANDLE hCom2;
HANDLE hCom3;

DCB		dcbCom1;
DCB		dcbCom2;
DCB		dcbCom3;

DWORD dwWritten;
DWORD dwRes;
DWORD dwRead;

COMMTIMEOUTS timeouts;

#endif

