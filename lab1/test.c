// #include "allocator.h"
// #include "test.h"

int round4(int num) {
  num += ((num % 4) == 0) ? 0 : (4 - (num % 4));

  return num;
}


void test() {
  myAllocInit();

  int size = 41;
  int size1 = 2;
  int size2 = 40;
  int size3 = 1000;
  int size4 = 45;
  int size5 = 80;

  void *ptr = myMalloc(size);
  void *ptr1 = myMalloc(size1);
  void *ptr2 = myMalloc(size2);
  void *ptr3 = myMalloc(size3);

  printf("Allocated memory address: %p\n", ptr);
  printf("Size of memory: %lu\texpected: %d\n", sizeOfMem(ptr), round4(size));
  printf("Allocated memory address: %p\n", ptr1);
  printf("Size of memory: %lu\texpested: %d\n", sizeOfMem(ptr1), round4(size1));
  printf("Allocated memory address: %p\n", ptr2);
  printf("Size of memory: %lu\texpected: %d\n", sizeOfMem(ptr2), round4(size2));
  printf("Allocated memory address: %p\n", ptr3);
  printf("Size of memory: %lu\texpected: %d\n", sizeOfMem(ptr3), round4(size3));

  void *ptr4 = myRealloc(ptr, size4);
  printf("Reallocated memory address: %p\texpected: %p\n", ptr4, ptr3 + 1008);
  printf("Size of memory: %lu\texpected: %d\n", sizeOfMem(ptr4), round4(size4));

  myFree(ptr);
  printf("Free memory: %p\n", ptr);

  myFree(ptr2);
  printf("Free memory: %p\n", ptr2);

  ptr1 = myRealloc(ptr1, size5);
  printf("Reallocated memory address: %p\texpected: %p\n", ptr1, ptr);
  printf("Size of memory: %lu\texpected: %d\n", sizeOfMem(ptr1), round4(size5));

  ptr = myMalloc(32);
  printf("Allocated memory: %p\n", ptr);
  printf("Size of memory: %lu\n", sizeOfMem(ptr));

  ptr = myMalloc(2);
  printf("Allocated memory: %p\n", ptr);
  printf("Size of memory: %lu\n", sizeOfMem(ptr));
}

void main() {
  test();
}
