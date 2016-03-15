#include "dataBuffer.h"

void initDataBuffer(DataBuffer* buffer)
{
	int i = 0;

	for(i = 0; i < BUFFER_SIZE; i++)
	{
		buffer->datas[i].acR = 0;
		buffer->datas[i].acIR = 0;
		buffer->datas[i].dcR = 0;
		buffer->datas[i].dcIR = 0;
	}

	buffer->index = 42;
}

void push_front(DataBuffer* buffer, Absorp absorp)
{
	buffer->index--;
	
	if(buffer->index == -1)
	{
		buffer->index = BUFFER_SIZE - 1;
	}

	buffer->datas[buffer->index] = absorp;
}

Absorp at(DataBuffer* buffer, int index)
{
	return buffer->datas[ (buffer->index + index) % BUFFER_SIZE];
}
