#ifndef DATABUFFER
#define DATABUFFER

#define BUFFER_SIZE 50

struct Data
{
	int acR;
	int arIR;
};
typedef struct Data Data;

struct DataBuffer
{
	Data datas[BUFFER_SIZE]
	int index;
};
typedef struct DataBuffer DataBuffer;

void initDataBuffer(DataBuffer* buffer);
void push_front(DataBuffer* buffer, Data data);
Data at(DataBuffer*, int index);

#endif