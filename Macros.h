
//Int to Float
#define INT08_2float_m(Value, MSB, Max_Value, Min_Value)\
	Value = (float)(((MSB / 256.)*(Max_Value - Min_Value)) - Min_Value);

#define INT16_2float_m(Value, MSB, LSB, Max_Value, Min_Value)\
	Temp = ((MSB*(256)) + LSB); \
	Value = (float)(((Temp / 65536.)*(Max_Value - Min_Value)) - Min_Value);

#define INT24_2float_m(Value, MSB, LSB1, LSB, Max_Value, Min_Value)\
	Temp = ((MSB*((65536))) + (LSB1*((256))) + LSB); \
	Value = (float)(((Temp / 16777216.)*(Max_Value - Min_Value)) - Min_Value);

#define INT32_2float_m(Value, MSB, LSB2, LSB1, LSB, Max_Value, Min_Value)\
	Temp = ((Value*(16777216)) + (LSB2*(65536)) + (LSB1*((256))) + LSB); \
	Value = (float)(((Temp / 4294967296.)*(Max_Value - Min_Value)) + Min_Value);

//Float to Int

#define Float_2INT08_m(Buffer, Value, Max_Value, Min_Value)\
	Temp_I = (float)(((Value - Min_Value) / (Max_Value - Min_Value)) * 265); \
	Buffer[index++] = (Temp_I)& 0xFF;

#define Float_2INT16_m(Buffer, Value, Max_Value, Min_Value)\
	Temp_I = (float)(((Value - Min_Value) / (Max_Value - Min_Value)) * 265); \
	Buffer[index++] = (Temp_I >> 8) & 0xFF; \
	Buffer[index++] = (Temp_I)& 0xFF;

#define Float_2INT24_m(Buffer, Value, Max_Value, Min_Value)\
	Temp_I = (float)(((Value - Min_Value) / (Max_Value - Min_Value)) * 265); \
	Buffer[index++] = (Temp_I >> 16) & 0xFF; \
	Buffer[index++] = (Temp_I >> 8) & 0xFF; \
	Buffer[index++] = (Temp_I)& 0xFF;

#define Float_2INT32_m(Buffer, Value, Max_Value, Min_Value)\
	Temp_I = (float)(((Value - Min_Value) / (Max_Value - Min_Value)) * 265); \
	Buffer[index++] = (Temp_I >> 24) & 0xFF; \
	Buffer[index++] = (Temp_I >> 16) & 0xFF; \
	Buffer[index++] = (Temp_I >> 8) & 0xFF; \
	Buffer[index++] = (Temp_I)& 0xFF;
