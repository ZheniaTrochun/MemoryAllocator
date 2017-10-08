#include <unistd.h>
#include <stdio.h>

int isInit = 0;
void *memoryStart;
void *lastAdress;

struct controlBlock {
  int isAvailable;
  int size;
};

void myAllocInit();
void myFree(void *firstByte);
void *myMalloc(long size);
void *myRealloc(void *firstByte, int newSize);

long unsigned int sizeOfMem(void *firstByte);
