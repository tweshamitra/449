#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

struct Block {
    int occ;
    int size;
    struct Block *prev;
    struct Block *next;
};
struct Block *head = NULL;
struct Block *find_block(int size){
    struct Block *to_return = NULL;
    struct Block *curr = head;
    while(curr!=NULL){
        if(curr->occ == 0){           
            if(curr->size > size){
                if(to_return == NULL || curr->size <= to_return->size){
                    to_return = curr;
                    if(curr->size == to_return->size){
                        to_return->next = curr ->next;
                        return to_return;
                        break;
                    }
                }
            }
        }
        curr = curr->next;
    }
    return NULL;
}
void *my_malloc(int size){
    void *block;
    struct Block *get_block = NULL;
    if(size == 0){
        return NULL;
    }
    get_block = find_block(size);   
    if(get_block == NULL){
        block = sbrk(size + sizeof(struct Block));
        
        if(block == (void*) -1){
            return NULL;
        }
        get_block = block;
        get_block->size = size +sizeof(struct Block);
        get_block->occ = 1;
        get_block->next = NULL;
        if(head == NULL){
            head = get_block;
            head->prev = NULL;    
        }
    }
    else{        
        get_block->occ = 1;
    }
    return (void*) (get_block + 1);

}
void my_free(void *data){
    void *heap_location;
    heap_location = sbrk(0);
    struct Block *block_to_remove = (struct Block *) data -1;
    void *curr_loc = data + block_to_remove ->size;
    //find the block to remove if the block is at the end of the heap
    int size_to_remove = sizeof(struct Block) + block_to_remove -> size;
    if(curr_loc == heap_location){
            while(block_to_remove != NULL){
                block_to_remove = block_to_remove->next;
            }
        
        sbrk(0 - size_to_remove);
    }
    block_to_remove->occ = 0;

}
/** @brief Dump the contents of the heap.
 *
 *  Traverse the heap starting from the head of the list and print
 *  each block.  While traversing, check the integrity of the heap
 *  through various assertions.
 *
 *  @return Void.
 */
 void dump_heap()
 {
   struct Block *cur;
   printf("brk: %p\n", sbrk(0));
   printf("head->");
   
   for(cur = head; cur != NULL; cur = cur->next) {
     printf("[%d:%d:%d]->", cur->occ, (char*)cur - (char*)head, cur->size);
     fflush(stdout);
     assert((char*)cur >= (char*)head && (char*)cur + cur->size <= (char*)sbrk(0)); // check that block is within bounds of the heap
     if(cur->next != NULL) {
       assert(cur->next->prev == cur); // if not last block, check that forward/backward links are consistent
       assert((char*)cur + cur->size == (char*)cur->next); // check that the block size is correctly set
     }
   }
   printf("NULL\n");
 }
 
