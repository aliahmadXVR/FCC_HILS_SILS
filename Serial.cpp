#include "stdafx.h"
#define Serial_Def
#include "Serial.h"

BOOL Serial::Create_Port(LPCSTR Comport_No, HANDLE * hComm, DCB * dcbComm)
{

BOOL fSuccess;

	*hComm = CreateFile((LPCSTR) Comport_No ,   // com4 is ready to communicate ==> open the port
			GENERIC_READ | GENERIC_WRITE,
			0,
			0,
			OPEN_EXISTING,
			0,
			0);
	if (*hComm  == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == 2)
		{
			std::cout << "Port is not available!" << endl;
		}
		if (GetLastError() == 5)
		{
			std::cout << "Port is not available!" << endl;
		}
		return(0);
	}
	
	GetCommState( *hComm , dcbComm );
	
	dcbCom1.BaudRate = 9600;
	dcbCom1.fParity = FALSE;//TRUE;
	dcbCom1.fOutxCtsFlow = FALSE;
	dcbCom1.fOutxDsrFlow = FALSE;
	dcbCom1.fOutX = FALSE;
	dcbCom1.fInX = FALSE;
	dcbCom1.ByteSize = 8;
	dcbCom1.Parity = NOPARITY;//EVENPARITY;
	dcbCom1.StopBits = ONESTOPBIT;

	fSuccess = SetCommState( *hComm , (LPDCB ) dcbComm );
	if (fSuccess == 0)
	{
		std::cout << "Unable to set parameters" << endl;
		return (0);
	}
	
	fSuccess = SetupComm(	*hComm , Rx_FRAME_LENGTH_COM1, Tx_FRAME_LENGTH_COM1);	
	if (fSuccess == 0)
	{
		std::cout << "Unable to set Buffer" << endl;
		return (0);
	}
	timeouts.ReadIntervalTimeout          = 0;
	timeouts.ReadTotalTimeoutMultiplier   = 1;
	timeouts.ReadTotalTimeoutConstant     = 1;
	timeouts.WriteTotalTimeoutMultiplier  = 1;
	timeouts.WriteTotalTimeoutConstant    = 1;

	if(!SetCommTimeouts ( *hComm ,  &timeouts))
	{
		std::cout << "Error in setting TimeOut" << endl;

		return (0);
	}
	std::cout << "Serial port has Initialized" << endl;
	return (1);
}

DWORD Serial::Write(HANDLE hComm, char * lpBuf, int dwToWrite)   // A good working function
{
	BOOL Success;
	Success = WriteFile( hComm,		// handle to output port
							lpBuf,					// data buffer to be written to port
							(DWORD) dwToWrite,			// no of bytes to write
							&dwWritten,				// no of bytes written
							NULL);//&olw);					// overlapped structure
	return (dwWritten);

}


DWORD Serial::Read(HANDLE hComm,char * lpBuf, int dwToRead)
{
	if(!(ReadFile(hComm, lpBuf, (DWORD) dwToRead, &dwRead, NULL)) || (dwRead != dwToRead ) )
	{
		return (0);
	}
	else
	{
		std::cout << (char*)lpBuf;
		return (dwRead);
	}	
}



void Serial::Initialize_Port()
{
	SetConsoleTitle("Serial Initialization Terminal");  // To change the name of the Console
	Create_Port( "COM1",&hCom1,&dcbCom1); 

	char lpBuf[50];
	lpBuf[0]= 97;
	while(true)
	{
	//	Serial_Read(hCom1,lpBuf , 1 );
	//	Write(hCom1, lpBuf, 1);
		Sleep(1);
	
	}
}







/*
void Serial_Write()
{
		char c =97;
		WriteABuffer((char*)&c, 1);

	
}
*/


/*
BOOL Serial_Initialize(HANDLE hComm)
{

BOOL fSuccess;

	hCom1 = CreateFile("COM1",   // com4 is ready to communicate ==> open the port
			GENERIC_READ | GENERIC_WRITE,
			0,
			0,
			OPEN_EXISTING,
			0,
			0);
	if (hCom1 == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == 2)
		{
			std::cout << "Port is not available!" << endl;
		}
		if (GetLastError() == 5)
		{
			std::cout << "Port is not available!" << endl;
		}
		return(0);
	}
	
	GetCommState( hCom1, &dcbCom1 );
	
	dcbCom1.BaudRate = 9600;
	dcbCom1.fParity = FALSE;//TRUE;
	dcbCom1.fOutxCtsFlow = FALSE;
	dcbCom1.fOutxDsrFlow = FALSE;
	dcbCom1.fOutX = FALSE;
	dcbCom1.fInX = FALSE;
	dcbCom1.ByteSize = 8;
	dcbCom1.Parity = NOPARITY;//EVENPARITY;
	dcbCom1.StopBits = ONESTOPBIT;

	fSuccess = SetCommState( hCom1, &dcbCom1 );
	if (fSuccess == 0)
	{
		std::cout << "Unable to set parameters" << endl;
		return (0);
	}
	
	fSuccess = SetupComm(	hCom1, Rx_FRAME_LENGTH_COM1, Tx_FRAME_LENGTH_COM1);	
	if (fSuccess == 0)
	{
		std::cout << "Unable to set Buffer" << endl;
		return (0);
	}
	timeouts.ReadIntervalTimeout          = 0;
	timeouts.ReadTotalTimeoutMultiplier   = 1;
	timeouts.ReadTotalTimeoutConstant     = 1;
	timeouts.WriteTotalTimeoutMultiplier  = 1;
	timeouts.WriteTotalTimeoutConstant    = 1;

	if(!SetCommTimeouts ( hCom1,  &timeouts))
	{
		std::cout << "Error in setting TimeOut" << endl;
		return (0);
	}
	std::cout << "Serial port has Initialized" << endl;
	return (1);
}

*/