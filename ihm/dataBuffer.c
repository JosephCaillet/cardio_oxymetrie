//
// Created by joseph on 16/03/16.
//

#include "dataBuffer.h"

void initBuffer(DataBuffer* db)
{
	for(int i = 0; i < TAILLE_BUFFER; i++)
	{
		db->data[i].x = 0;
		db->data[i].y = 0;
	}
	db->index = 0;
}

void pushBackBuffer(DataBuffer* db, Coord coord)
{
	db->data[db->index] = coord;
	db->index + 1 ? db->index++ : (db->index = 0);
}

Coord atBuffer(DataBuffer* db, int index)
{
	return db->data[index];
}