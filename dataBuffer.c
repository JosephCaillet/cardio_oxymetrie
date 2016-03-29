#include "dataBuffer.h"

void initDataBuffer(DataBuffer* buffer)
{
	int i = 0;

	for(i = 0; i < BUFFER_SIZE; i++)
	{
		buffer->datas[i].acr = 0;
		buffer->datas[i].acir = 0;
		buffer->datas[i].dcr = 0;
		buffer->datas[i].dcir = 0;
	}

	buffer->index = 42;
}

void push_front(DataBuffer* buffer, absorp absorp)
{
	buffer->index--;
	
	if(buffer->index == -1)
	{
		buffer->index = BUFFER_SIZE - 1;
	}

	buffer->datas[buffer->index] = absorp;
}

absorp at(DataBuffer* buffer, int index)
{
	return buffer->datas[ (buffer->index + index) % BUFFER_SIZE];
}
