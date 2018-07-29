# Ram_managing_cpp
//better understanding of malloc() and free() function //
//be patient to understand code //i have well commented it//

This is a program to understand how operating system manages its free and allocated memory
There is a fixed Ram taken as a memory array of size 10
OS uses two linked list- freelist and alloclist to manage memory

freelist contain node containing - a free memory address , its size and next pointer
alloclist contain node containing - a allocted memory address,its size and next pointer

when there is demand of free memory by mymalloc(int rsize) function it searches freelist if available it allocate that memory and
mark/add it to alloclist 

when we call free(int* a) it remove the node that contain the address pointed by 'pointer a ' from alloclist and add it to freelist
and if adjacent memory is free it also join them in freelist
