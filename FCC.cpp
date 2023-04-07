#include "stdafx.h"

#include "FCC.h"

void Receive_FCC_Data(){}

void Decode_FCC_Data(){}

void Encode_FCC_Data(){}

void Transmit_FCC_Data(){}


/*
void HILS_Recieve(void)
{
	static char Search_For;
	static int Data;
	static int Cal_CRC;
	struct mYComport Com_Hils;

	char Buff[20];
	
	while (true)
	{
		//
		if (Com_Hils.Serial_Read_Bytes(Buff, 0, 1) != 0)
		{

			switch (Search_For)
			{
			case 'F':
			{

				if (Buff[0] == 'F')
				{
					Buff_Hils_Received[0] = Buff[0];
					Search_For = 'D';
				}
				break;
			}
			case 'D':
			{
				if (Buff[0] == 'D')
				{
					Buff_Hils_Received[1] = Buff[0];
					Search_For = 'M';
				}
				else if (Buff[0] == 'F')
				{
					Search_For = 'D';
				}
				else
				{
					Search_For = 'F';
				}
				break;
			}

			case 'M':
			{
				if (Buff[0] == 'M')
				{
					Buff_Hils_Received[2] = Buff[0];
					Search_For = 'L';
				}
				else if (Buff[0] == 'F')
				{
					Search_For = 'D';
				}
				break;
			}
					//Data Length
			case 'L':
			{
				Buff_Hils_Received[3] = Buff[0];
				Search_For = 'G';
				break;
			}
					//Data
			case 'G':
			{
				Buff_Hils_Received[Data++] = Buff[0];
				Cal_CRC ^= Buff[0];
				if (Data == 12)
				{
					Search_For = 'C';
				}
				break;
			}
		
				//CRC
			case 'C':
			{
				if (Cal_CRC == Buff[0])
				{
					cout << "valid data";
				}
				else
				{
					cout << "valid data";
				}
					return;
			}
		}

		}
		else
		{
			break; //return
		}
	}
}


void Decode_Hils(void)
{
	int Data_Length, Flag1, Flag2, Elevator, Aileron, Rudder, Throttle;
	int Temp;

	Data_Length = Buff_Hils_Received[3];
	Flag1 = Buff_Hils_Received[4];
	Flag2 = Buff_Hils_Received[5];
	INT16_2float_m(Elevator, Buff_Hils_Received[6], Buff_Hils_Received[7], 60., -60.);
	INT16_2float_m(Aileron, Buff_Hils_Received[8], Buff_Hils_Received[9], 60., -60.);
	INT16_2float_m(Aileron, Buff_Hils_Received[10], Buff_Hils_Received[11], 60., -60.);
	Throttle = Buff_Hils_Received[11];
}


void Transmit_Hils(void)
{
	int CRC_Trans;
	Buff_HIls_Transmit[0] = 'F';
	Buff_HIls_Transmit[1] = 'D';
	Buff_HIls_Transmit[2] = 'M';
	Buff_HIls_Transmit[3] = Length;
	Buff_HIls_Transmit[4] = Mac;
	Buff_HIls_Transmit[5] = Flag1;
	Buff_HIls_Transmit[6] = Flag2;
	Buff_HIls_Transmit[7] = Flag3;

	Float_2INT16_m(Buff_HIls_Transmit, Roll_Rate, 400., -400.);
	Float_2INT16_m(Buff_HIls_Transmit, Pitch_Rate, 400., -400.);
	Float_2INT16_m(Buff_HIls_Transmit, Yaw_Rate, 400., -400.);
	Float_2INT16_m(Buff_HIls_Transmit, Roll_Angle, 180., -180.);
	Float_2INT16_m(Buff_HIls_Transmit, Pitch_Angle, 90., -90.);
	Float_2INT16_m(Buff_HIls_Transmit, Yaw_Angle, 180., -180.);

	Float_2INT32_m(Buff_HIls_Transmit, Latitude, 90., -90.);
	Float_2INT32_m(Buff_HIls_Transmit, Longitude, 180., -180.);

	Float_2INT24_m(Buff_HIls_Transmit, Altitude, 50000., -100.);
	Float_2INT08_m(Buff_HIls_Transmit, Throttle_Actual, 1., 0.);

	for (int i = 4; i <= 32; i++)
	{
		CRC_Trans ^= Buff_HIls_Transmit[i];
	}
	
	Buff_HIls_Transmit[33] = CRC_Trans & 0xFF;
}

*/