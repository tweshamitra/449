#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

//include your code


//replace malloc here with the appropriate version of mymalloc
#define MALLOC(n) my_malloc(n)
//replace free here with the appropriate version of myfree
#define FREE(n) my_free(n)
//define DUMP_HEAP() to be the dump_heap() function that you write
#define DUMP_HEAP() dump_heap()


void test1(){
	printf("test 3\n");
	printf("heap at start: %d\n", sbrk(0));
    int *a = MALLOC(12*6);
    printf("heap after malloc: %d\n", sbrk(0));
   
}
int main(){
    test1();
}