#include "dataBuffer.h"

void initDataBuffer(DataBuffer* buffer)
{
	int i = 0;

	for(i = 0; i < BUFFER_SIZE; i++)
	{
		buffer->datas[i].acR = 0;
		buffer->datas[i].acIR = 0;
	}

	data->index = 42;
}

void push_front(DataBuffer* buffer, Data data)
{
	buffer->index--;
	
	if(index == -1)
	{
		buffer->index = BUFFER_SIZE - 1;
	}

	buffer->datas[buffer->index] = data;
}

Data at(DataBuffer* buffer, int index)
{
	return buffer->datas[ (buffer->index + index) % BUFFER_SIZE];
}