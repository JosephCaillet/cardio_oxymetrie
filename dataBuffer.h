#ifndef DATABUFFER
#define DATABUFFER

#include "define.h"

#define BUFFER_SIZE 51

struct DataBuffer
{
	absorp datas[BUFFER_SIZE];
	int index;
};
typedef struct DataBuffer DataBuffer;

void initDataBuffer(DataBuffer* buffer);
void push_front(DataBuffer* buffer, absorp data);
absorp at(DataBuffer* buffer, int index);

#endif