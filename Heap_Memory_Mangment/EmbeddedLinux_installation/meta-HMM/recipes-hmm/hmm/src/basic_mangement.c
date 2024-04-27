#include "basic_mangement.h"



// declare a global variable to store the head of the linked list
FREELIST_DECL_SPECIFIERS LIST_INIT(free_list);



/**
 * @brief Initialize the memory allocator
 *
 * This function initializes the memory allocator.
 * It is called by the system before the program starts.
 *
 * */
void *malloc(size_t size) {

    void *retval = NULL;
    node_alloc_t *currblk = NULL;

    pthread_mutex_lock(&malloc_mutex); // Lock mutex before accessing shared data
    size = ((size + 7)/8) * 8;
    if (size == 0) {
        pthread_mutex_unlock(&malloc_mutex); // Unlock mutex on error
        return NULL;
    }
    
    list_for_each_entry(currblk, &free_list, node) {
        if (currblk->size >= size + MIN_ALLOC_SIZE) {
            retval = (void*) ((uintptr_t) currblk->block);
            break;
        }
    }

    if (retval) {
        if ((currblk->size - size) >= MIN_ALLOC_SIZE) {
            node_alloc_t *new_block = (node_alloc_t*) ((uintptr_t) (&currblk->block) + size);
            new_block->size = currblk->size - size - ALLOC_HEADER_SIZE;
            currblk->size = size;
	    currblk->free = 0;
            list_insert(&new_block->node, &currblk->node, currblk->node.next);
	}
	list_del(&currblk->node);
        
        retval = (void*) ((uintptr_t) retval + 1);
    } else {
        size_t total_size = size + sizeof(node_alloc_t);
	    void *ptr = sbrk(total_size);

        if (ptr == (void*) MAP_FAILED) {
            pthread_mutex_unlock(&malloc_mutex); // Unlock mutex on error
            return NULL;
        }

        node_alloc_t *header = (node_alloc_t*) ptr;
        header->size = size;
	header->free = 0;
        list_add(&currblk->node, &free_list);

        // Memory leak detection (basic): Maintain a counter for allocated blocks
        static int allocated_blocks = 0;
        allocated_blocks++;

        retval = (void*) ((uintptr_t) ptr + ALLOC_HEADER_SIZE);
    }

    pthread_mutex_unlock(&malloc_mutex); // Unlock mutex after operation

    return retval;
}


void fragmentaion_removal(void){
	node_alloc_t *curr = NULL;
	node_alloc_t *prev = NULL;
	node_alloc_t *temp = NULL;
	list_for_each_entry_safe(curr,temp,&free_list,node){
		if(!prev){
			if(((uintptr_t)&prev->block + prev->size) == (uintptr_t)curr->block){
				prev->size += ALLOC_HEADER_SIZE + curr->size;
				list_del(&curr->node);
				continue;
			}
			
		}
		prev = curr;
	}
}

/**
 * @brief Deallocate a block of memory
 * @param ptr Pointer to the block of memory to deallocate
 *
 * This function deallocates the block of memory pointed to by ptr.
 * If ptr is NULL, no operation is performed.
 * If the block is already deallocated, the behavior is undefined.
 * If the block is not allocated by malloc, the behavior is undefined.
 *
 * */
void free(void *ptr) {
  if (!ptr) {
    return;
  }

  pthread_mutex_lock(&malloc_mutex); // Lock mutex before accessing shared data

  // Convert pointer back to node_alloc_t structure
  node_alloc_t *curr_block = (node_alloc_t *)((uintptr_t)ptr - ALLOC_HEADER_SIZE);

  // Mark the block as free
  curr_block->free = 1;

  // Attempt to merge with adjacent free blocks
  node_alloc_t *prev = NULL;
  node_alloc_t *next = NULL;

  list_for_each_entry_safe(prev, next, &free_list, node) {			// check for the previous and next block
    if (prev && ((uintptr_t)&prev->block + prev->size) == (uintptr_t)curr_block) {
      // Merge with previous block
      prev->size += ALLOC_HEADER_SIZE + curr_block->size; // update the size of the previous block
      list_del(&curr_block->node); // delete the current block
      continue;
    }
    if (next && ((uintptr_t)curr_block->block + curr_block->size) == (uintptr_t)&next->block) { 
      // Merge with next block
      curr_block->size += ALLOC_HEADER_SIZE + next->size; // update the size of the current block
      list_del(&next->node); // delete the next block
    }
    break;
  }

  // Update allocated block counter (basic memory leak detection)
  static int allocated_blocks = 0;
  allocated_blocks--;

  pthread_mutex_unlock(&malloc_mutex); // Unlock mutex after operation
}



/**
 * @brief Add a block of memory to the free list
 * @param block Pointer to the block of memory to add
 * @param size Size of the block of memory
 *
 * This function adds a block of memory to the free list.
 * The block is added to the free list in ascending order of memory address.
 * */
void malloc_add_block(void *block, size_t size){
	node_alloc_t *new_block = (void*)align_up((uintptr_t)block,sizeof(void*));
	new_block->size = (uintptr_t)block + size - (uintptr_t)new_block - ALLOC_HEADER_SIZE;
	
	pthread_mutex_lock(&malloc_mutex);
	list_add(&new_block->node,&free_list);
	pthread_mutex_unlock(&malloc_mutex);
}

/*
 * @brief Allocate a block of memory and initialize it to zero
 * @param num Number of elements
 * @param size Size of each element
 * @return Pointer to the allocated block of memory
 *
 * This function allocates a block of memory for an array of num elements, each of size bytes.
 * The block of memory is initialized to zero.
 * If the allocation fails, the function returns NULL.
 * If the product of num and size exceeds SIZE_MAX, the function returns NULL.
 *
 * */
void* calloc(size_t num, size_t size)
{	
	// Check for overflow 
	// If the product of num and size exceeds SIZE_MAX, the function returns NULL.
	 
	if((num >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) && num > 0 && SIZE_MAX / num < size)
	{
		return NULL;
	}

	size_t total_size = num * size;
	void* ptr = malloc(total_size);

	if(!ptr)
		return NULL;
	
	memset(ptr, 0, total_size);

	return ptr;

}


/**
 * @brief Reallocate a block of memory
 * @param ptr Pointer to the block of memory to reallocate
 * @param size New size of the block of memory
 * @return Pointer to the reallocated block of memory
 *
 * This function changes the size of the block of memory pointed to by ptr to size bytes.
 * The contents of the block are preserved up to the minimum of the old and new sizes.
 * If the new size is larger than the old size, the additional memory is uninitialized.
 * If ptr is NULL, the function behaves like malloc.
 * If size is zero, the function behaves like free.
 * If the allocation fails, the function returns NULL.
 * */
void* realloc(void* ptr, size_t size)
{
	void* new_data = NULL;

	if(size)
	{
		if(!ptr)
		{
			return malloc(size);
		}

		new_data = malloc(size);
		if(new_data)
		{
			memcpy(new_data, ptr, size);
			free(ptr); // we always move the data. free.
		}
	}

	return new_data;
}
