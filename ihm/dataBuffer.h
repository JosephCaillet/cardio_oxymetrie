//
// Created by joseph on 16/03/16.
//

#ifndef IHM_DATABUFFER_H
#define IHM_DATABUFFER_H

#define TAILLE_BUFFER 200

struct Coord
{
	int x;
	int y;
};
typedef struct Coord Coord;

struct DataBuffer
{
	Coord data[TAILLE_BUFFER];
	int index;
};
typedef struct DataBuffer DataBuffer;

void initBuffer(DataBuffer* db);
void pushBackBuffer(DataBuffer* db, Coord coord);
Coord atBuffer(DataBuffer* db, int index);

#endif //IHM_DATABUFFER_H