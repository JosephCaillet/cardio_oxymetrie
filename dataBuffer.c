#include "dataBuffer.h"

void initDataBuffer(DataBuffer* buffer)
{
	int i = 0;

	for(i = 0; i < BUFFER_SIZE; i++)
	{
		(*buffer)[i].acR = 0;
		(*buffer)[i].acIR = 0;
	}
}

void push_front(DataBuffer* buffer, Data data)
{

}

Data at(DataBuffer*, int index)
{

}