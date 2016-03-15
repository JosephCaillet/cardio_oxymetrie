#ifndef DATABUFFER
#define DATABUFFER

#define BUFFER_SIZE 51

struct Oxy
{
	int spo2;
	int pouls;
};
typedef struct Oxy Oxy;

struct Absorp
{
	float acR;
	float acIR;
	float dcR;
	float dcIR;
};
typedef struct Absorp Absorp;

struct DataBuffer
{
	Absorp datas[BUFFER_SIZE];
	int index;
};
typedef struct DataBuffer DataBuffer;

void initDataBuffer(DataBuffer* buffer);
void push_front(DataBuffer* buffer, Absorp data);
Absorp at(DataBuffer* buffer, int index);

#endif