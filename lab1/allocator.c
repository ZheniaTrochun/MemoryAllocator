#include "allocator.h"

void divBlock(void *firstByte, int size);
void *findPrevBlock(void *firstbyte);
void *connectBlocks(void *first, void *second);
void copyData(unsigned int *read, unsigned int *write, int size);



void myAllocInit() {
  lastAdress = sbrk(0);

  memoryStart = lastAdress;

  isInit = 1;
}



void myFree(void *firstByte) {
  struct controlBlock *control;
  control = firstByte - sizeof(struct controlBlock);
  control->isAvailable = 1;

  void *prev = findPrevBlock(control);

  if (prev != NULL) {
    struct controlBlock *prevControl = prev;

    if (prevControl->isAvailable) {
      control = connectBlocks(prevControl, control);
    }
  }


  void *nextPtr = control + control->size;

  if (nextPtr < lastAdress) {
    struct controlBlock *nextControl = nextPtr;

    if(nextControl->isAvailable) {
      connectBlocks(control, nextControl);
    }
  }
}



void *myMalloc(long size) {
  void *curr;
  struct controlBlock *currControll;
  void *location;

  if (! isInit) {
    myAllocInit();
  }

  size += (size % 4 == 0) ? 0 : (4 - (size % 4));
  size += sizeof(struct controlBlock);

  location = 0;
  curr = memoryStart;

  while (curr != lastAdress) {
    currControll = (struct controlBlock *)curr;

    if (currControll->isAvailable) {
      if (currControll->size == size) {
        currControll->isAvailable = 0;

        location = curr;

        break;
      } else if (currControll->size > size) {
        currControll->isAvailable = 0;
        location = curr;

        divBlock(curr, size);
        break;
      }
    }

    curr += currControll->size;
  }

  if (! location) {
    sbrk(size);

    location = lastAdress;
    lastAdress += size;

    currControll = location;
    currControll->isAvailable = 0;
    currControll->size = size;
  }

  location += sizeof(struct controlBlock);

  return location;
}



long unsigned int sizeOfMem(void *firstByte) {
  struct controlBlock *control = firstByte - sizeof(struct controlBlock);
  return ((struct controlBlock *)(firstByte - sizeof(struct controlBlock)))->size - sizeof(struct controlBlock);
}



void divBlock(void *firstByte, int size) {
  struct controlBlock *control = firstByte;

  int newBlockSize = control->size - size;

  if (newBlockSize <= sizeof(struct controlBlock)) {
    return;
  }

  struct controlBlock *newControlBlock  = firstByte + size;
  newControlBlock->isAvailable = 1;
  newControlBlock->size = newBlockSize;

  control->size = size;
}



void *findPrevBlock(void *firstbyte) {
  void *prev = memoryStart;
  struct controlBlock *prevControl = prev;

  void *curr = prev + prevControl->size;
  struct controlBlock *currControll = curr;

  while (curr < lastAdress) {

    if (curr == firstbyte) {
      return prev;
    }

    prev = curr;
    prevControl = currControll;

    curr += currControll->size;
    currControll = curr;
  }

  return NULL;
}


void *connectBlocks(void *first, void *second) {
  struct controlBlock *controlFirst = first;
  struct controlBlock *controlSecond = second;

  controlFirst->size += controlSecond->size;

  return first;
}


void *myRealloc(void *firstbyte, int newSize) {
  struct controlBlock *control = firstbyte - sizeof(struct controlBlock);

  newSize += sizeof(struct controlBlock);

  if (newSize == control->size)
    return firstbyte;

  if (newSize < control->size) {
    divBlock(control, newSize);
    return firstbyte;
  }

  struct controlBlock *prevControl = findPrevBlock(control);
  struct controlBlock *nextControl = control + control->size;

  if (prevControl) {
    printf("prev %p\n", prevControl);
    printf("prev available %p\n", prevControl->isAvailable);
    printf("prev size %p\n", prevControl->size);
  }

  printf("control %p\n", control);
  printf("control available %p\n", control->isAvailable);
  printf("control size %p\n", control->size);

  // if ()
  printf("next %p\n", nextControl);
  printf("next available %p\n", nextControl->isAvailable);
  printf("next size %p\n", nextControl->size);

  if ((nextControl < lastAdress) && nextControl->isAvailable && ((prevControl->size + control->size) >= newSize)) {
    control->size += nextControl->size;

    if (control->size > newSize) {
      divBlock(prevControl, newSize);
    }

    return control + sizeof(struct controlBlock);
  }


  if (prevControl && prevControl->isAvailable && ((prevControl->size + control->size) >= newSize)) {
    copyData(firstbyte, prevControl + sizeof(struct controlBlock), control->size);

    prevControl->isAvailable = 0;
    prevControl->size += control->size;

    if (prevControl->size > newSize) {
      divBlock(prevControl, newSize);
    }

    return prevControl + sizeof(struct controlBlock);
  }

  if ((nextControl < lastAdress) && nextControl->isAvailable && prevControl &&
      prevControl->isAvailable && ((prevControl->size + control->size + nextControl->size) >= newSize)) {

    copyData(firstbyte, prevControl + sizeof(struct controlBlock), control->size);

    prevControl->size += control->size;
    prevControl->size += nextControl->size;

    divBlock(prevControl, newSize);

    return prevControl + sizeof(struct controlBlock);
  }

  void *newLocation = myMalloc(newSize - sizeof(struct controlBlock));
  copyData(firstbyte, newLocation, control->size);

  myFree(firstbyte);

  return newLocation;
}



void copyData(unsigned int *read, unsigned int *write, int size) {
  for (int i = 0; i < size; i++) {
    *(write + i) = *(read + i);
  }
}





// void main() {
//   myAllocInit();
//
//   printf("Size of controlBlock: %lu\n", sizeof(struct controlBlock));
//
//   void *ptr = myMalloc(41);
//   void *ptr1 = myMalloc(2);
//   void *ptr2 = myMalloc(40);
//
//   printf("Allocated memory: %p\n", ptr);
//   printf("Size of memory: %lu\n", sizeOfMem(ptr));
//   printf("Allocated memory: %p\n", ptr1);
//   printf("Size of memory: %lu\n", sizeOfMem(ptr1));
//   printf("Allocated memory: %p\n", ptr2);
//   printf("Size of memory: %lu\n", sizeOfMem(ptr2));
//
//   ptr = myRealloc(ptr, 45);
//   printf("Reallocated memory: %p\n", ptr);
//   printf("Size of memory: %lu\n", sizeOfMem(ptr));
//   // printf("Size of memory: %lu\n", sizeOfMem(ptr));
//   myFree(ptr);
//   printf("Free memory: %p\n", ptr);
//   myFree(ptr1);
//   printf("Free memory: %p\n", ptr1);
//   myFree(ptr2);
//   printf("Free memory: %p\n", ptr2);
//
//   printf("Memory start %p\n", memoryStart);
//   ptr = myMalloc(32);
//   printf("Allocated memory: %p\n", ptr);
//   printf("Size of memory: %lu\n", sizeOfMem(ptr));
//
//   ptr = myMalloc(2);
//   printf("Allocated memory: %p\n", ptr);
//   printf("Size of memory: %lu\n", sizeOfMem(ptr));
//
//   // printf("123\n");
// }
