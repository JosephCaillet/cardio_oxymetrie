#ifndef DATABUFFER
#define DATABUFFER

#define BUFFER_SIZE 50

struct Data
{
	int ACr;
	int ACir
};
typedef struct Data Data;

struct DataBuffer
{
	Data datas[BUFFER_SIZE]
	int position;
};
typedef struct DataBuffer DataBuffer;

#endif