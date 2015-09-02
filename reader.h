#ifndef __READER_INCLUDED
#define __READER_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int* array;
    int used;
    int size;
} intlist;

typedef struct {
    float x;
    float y;
}vector;




void openData(char* path);
vector readNodeLocation(int node);
intlist readNodeNeighbourList(int node);

#endif
