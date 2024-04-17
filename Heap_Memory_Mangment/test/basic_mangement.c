#include "basic_mangement.h"



//search_free_block
//traverse the linked list and see if already exist a block of memeory is free and can fit in size
header_t *search_freeblock(size_t size){
        header_t* curr = head;
        while(curr){
                if (curr->s.is_free && curr->s.size >= size)
                        return curr;
                curr = curr->s.next;
        }
        return NULL;
}


//The malloc(size) function allocates size bytes of memory and returns a pointer to the allocated memory.
void *mymalloc(size_t size)
{
	printf("Hello from wafdunix malloc implemntation\n");
	size_t total_size;
	void* block;
	header_t *header;
	//we check if requested size is zero , return NULL
	if (!size){
		return NULL;
	}
	//for valid size aquire lock and search for block
	pthread_mutex_lock(&global_malloc_lock);
	header = search_freeblock(size);
	//if large free block is found , mark the block as not-free, release global lock , and return pointer for the block
	
	if(header){
		header->s.is_free = 0;
		pthread_mutex_unlock(&global_malloc_lock);
		return (void*) (header+1);	//When we do (header + 1), it points to the byte right after the end of the header.
	}

	total_size = sizeof(header_t) + size;
	// call sbrk with the given size on success , size bytes are allocated on theheap 
	block = sbrk(total_size);
	if(block == (void*) -1){
		pthread_mutex_unlock(&global_malloc_lock);
		return NULL;
	}
	header = block;
	header->s.size = size ; 
       	header->s.is_free = 0;
	header->s.next = NULL;
	//We fill this header with the requested size (not the total size) and mark it as not-free.
	//We update the next pointer, head and tail so to reflect the new state of the linked list	
	if(!head){
		head = header;
	}
	if(tail){
		tail->s.next = header;
	}
	tail = header;
	pthread_mutex_unlock(&global_malloc_lock);
	return (void*)(header+1);
}



//free() has to first determine if the block-to-be-freed is at the end of the heap if it is ,we can release it
void myfree(void *block)
{
	printf("\nHello from wafdunix free implemntation");
	header_t *header, *tmp;
	void *programbreak;
	//first we need to get the header of the block we want to free 
	if(!block)
		return;
	pthread_mutex_lock(&global_malloc_lock);
	header = (header_t*) block-1;

	programbreak = sbrk(0);

	// To check if the block to be freed is at the end of the heap, we first find the end of the current block. compared with the program break.
	if((char*)block + header->s.size == programbreak){
		if(head == tail){
			head = tail = NULL;
		}else{
			tmp = head;
			while(tmp){
				if(tmp->s.next == tail){
					tmp->s.next = NULL;
					tail = tmp;
				}
				tmp = tmp->s.next;
			}
		
		}
		//the amount of memory to be released is calculated. This the sum of sizes of the header and the acutal block:
		sbrk(0- sizeof(header_t) - header->s.size);
		pthread_mutex_unlock(&global_malloc_lock);
		return;
	}
	header->s.is_free = 1;
	pthread_mutex_unlock(&global_malloc_lock);
}





/* A debug function to print the entire link list */
void print_mem_list()
{
	header_t *curr = head;
	printf("head = %p, tail = %p \n", (void*)head, (void*)tail);
	while(curr) {
		printf("addr = %p, size = %zu, is_free=%u, next=%p\n",
			(void*)curr, curr->s.size, curr->s.is_free, (void*)curr->s.next);
		curr = curr->s.next;
	}
}

//the calloc fn. allocates memory for an array of num elements of numsize bytes each and initialise it to zero , returns pointer for the allocated memory.

void *calloc(size_t num, size_t nsize){
	printf("Hello from wafdunix calloc implemntation");
        size_t size;
        void *block;
        if(!num || !nsize){
                return NULL;
        }
        size = num * nsize;
        if(nsize != size /num)  // check for multiplicative overflow
                return NULL;
        block = mymalloc(size);
        if(!block)
                return NULL;
        memset(block,0,size);
        return block;
}

//realloc is a fn. changes the size of a given memory block 

void *realloc(void *block, size_t size){
	printf("Hello from wafdunix realloc implemntation");
	header_t *header;
	void *ret;
	// if the block has already the requeted size ther's nothing to be done 
	if(!block || !size)
	       return mymalloc(size);
	header = (header_t*)block - 1;
	// if the current block doesn't have the requested size , malloc can get a block of the requested size 
	if (header->s.size >= size)
		return block;
	ret = mymalloc(size);
	//relocate contents to the new bigger block using memcpy() , freeing the old block
	if(ret){
		memcpy(ret,block,header->s.size);
		myfree(block);
	}

	return ret;
}
