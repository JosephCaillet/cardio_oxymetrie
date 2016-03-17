//
// Created by joseph on 16/03/16.
//

#include "dataBuffer.h"

void initBuffer(DataBuffer* db)
{
	for(int i = 0; i < TAILLE_BUFFER; i++)
	{
		db->data[i] = INIT_VALUE;
	}
	db->index = 0;
}

void pushBackBuffer(DataBuffer* db, int data)
{
	db->data[db->index] = data;
	db->index + 1 != TAILLE_BUFFER ? db->index++ : (db->index = 0);
}

int atBuffer(DataBuffer* db, int index)
{
	return db->data[index];
}