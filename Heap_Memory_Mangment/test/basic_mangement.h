#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <stdio.h>

//Header structure , I put it as a union to guarntees that the header of the block is aligned .
//End of the header is the actual memory block begins .

typedef char ALIGN[16];
union header {
        struct {
                size_t size;
                unsigned is_free;
                union header *next;             //to keep track of the list
        }s;
        ALIGN st;
};
typedef union header header_t;
header_t *head,*tail;


//basic locking mechanism ,to prevent that two or more threads accessing the memory
//before every action on memory ,we have to aquire the lock and once we done 

pthread_mutex_t global_malloc_lock;

//functions


header_t *search_freeblock(size_t size);
void *mymalloc(size_t size);
void myfree(void *block);
void print_mem_list();
void *calloc(size_t num, size_t nsize);
void *realloc(void *block, size_t size);
