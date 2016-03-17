//
// Created by joseph on 16/03/16.
//

#ifndef IHM_DATABUFFER_H
#define IHM_DATABUFFER_H

#define TAILLE_BUFFER 800
#define INIT_VALUE 30

struct DataBuffer
{
	int data[TAILLE_BUFFER];
	int index;
};
typedef struct DataBuffer DataBuffer;

void initBuffer(DataBuffer* db);
void pushBackBuffer(DataBuffer* db, int data);
int atBuffer(DataBuffer* db, int index);

#endif //IHM_DATABUFFER_H