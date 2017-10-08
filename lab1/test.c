// #include "allocator.h"
// #include "test.h"

void test() {
  myAllocInit();

  // printf("Size of controlBlock: %lu\n", sizeof(struct controlBlock));

  void *ptr = myMalloc(41);
  void *ptr1 = myMalloc(2);
  void *ptr2 = myMalloc(40);
  void *ptr3 = myMalloc(1000);

  printf("Allocated memory address: %p\n", ptr);
  printf("Size of memory: %lu\texpected: %d\n", sizeOfMem(ptr), 44);
  printf("Allocated memory address: %p\n", ptr1);
  printf("Size of memory: %lu\texpested: %d\n", sizeOfMem(ptr1), 4);
  printf("Allocated memory address: %p\n", ptr2);
  printf("Size of memory: %lu\texpected: %d\n", sizeOfMem(ptr2), 40);
  printf("Allocated memory address: %p\n", ptr3);
  printf("Size of memory: %lu\texpected: %d\n", sizeOfMem(ptr3), 1000);

  void *ptr4 = myRealloc(ptr, 45);
  printf("Reallocated memory address: %p\n", ptr4);
  printf("Size of memory: %lu\texpected: %d\n", sizeOfMem(ptr4), 48);

  myFree(ptr);
  printf("Free memory: %p\n", ptr);
  // myFree(ptr1);
  // printf("Free memory: %p\n", ptr1);
  myFree(ptr2);
  printf("Free memory: %p\n", ptr2);

  ptr1 = myRealloc(ptr1, 80);
  printf("Reallocated memory address: %p\n", ptr1);
  printf("Size of memory: %lu\texpected: %d\n", sizeOfMem(ptr1), 80);

  // printf("Memory start %p\n", memoryStart);
  ptr = myMalloc(32);
  printf("Allocated memory: %p\n", ptr);
  printf("Size of memory: %lu\n", sizeOfMem(ptr));

  ptr = myMalloc(2);
  printf("Allocated memory: %p\n", ptr);
  printf("Size of memory: %lu\n", sizeOfMem(ptr));

  // printf("123\n");
}

void main() {
  test();
}
