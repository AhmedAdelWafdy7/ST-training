/*
 *	Author: Ahmed Adel Wafdy , WAFDUNIX
 *
 * */

#ifndef BASIC_MANAGEMENT_H_
#define BASIC_MANAGEMENT_H_

#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/mman.h>

//#include <stdio.h>				//for debugging purposes
//#include <stdlib.h>				//for debugging purposes
#include <stddef.h>				//for offsetof macro








/**
 * Define offsetof if we don't have it already
 */
#ifndef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER) __compiler_offsetof(TYPE, MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE*)0)->MEMBER)
#endif
#endif // offsetof

/**
 * Define container_of if we don't have it already
 */
#ifndef container_of
#ifdef __GNUC__
#ifndef __clang__
// Isolate the GNU-specific expression
#define container_of(ptr, type, member)                       \
	({                                                        \
		const __typeof__(((type*)0)->member)* __mptr = (ptr); \
		(type*)((uintptr_t)__mptr - offsetof(type, member));  \
	})
#else // we are clang - avoid GNU expression
#define container_of(ptr, type, member) ((type*)((uintptr_t)(ptr)-offsetof(type, member)))
#endif // GNU and not clang
#else
#define container_of(ptr, type, member) ((type*)((uintptr_t)(ptr)-offsetof(type, member)))
#endif // not GNU
#endif // container_of







/*
 * @brief : this is a linked list structure , it's used to keep track of the memory blocks.
 * it contains a pointer to the next block and a pointer to the previous block.
 * */
typedef struct ll_head{
	//pointer to the next block
	struct ll_head *next;
	//pointer to the previous block
	struct ll_head *prev;
}LinkedList_t;


//macros

/*
 * @brief : this macro is used to get the address of the structure that contains the member.
 * @param : ptr : pointer to the member LinkedList_t node.
 * @param : type : the type of the structure that contains the member.
 * @param : member : the member of the structure.
 *
 *
 * @return : the address of the structure that contains the member.
 * */
#define list_entry(ptr, type, member) container_of(ptr, type, member)


/*
 * @brief : this macro is used to get the first entry of the list.
 * @param : head : pointer to the head of the list.
 * @param : type : the type of the structure that contains the member.
 * @param : member : the member of the structure.
 *
 *
 * @return : the first entry of the list.
 * */
#define list_first_entry(head, type, member) list_entry((head)->next, type, member)

/*
 * @brief : this macro is is used to iterate over the list.
 * it will run as long as the pos is not equal to the head of the list.
 *
 * @param : pos : pointer to the current node.
 * @param : head : pointer to the head of the list.
 *
 * @return : the current node. pointer to the current node.
 * */
#define list_for_each(pos, head) for(pos = (head)->next; pos != (head); pos = pos->next)





/*
 * @brief : this macro is used to iterate over the list and copy current node pointer to the next node
 * it will run as long as the pos is not equal to the head of the list.
 * this macro is used to prevent the deletion of the current node.
 *
 * @param : pos : pointer to the current node.
 * @param : n : pointer to the next node.
 * @param : head : pointer to the head of the list.
 * @return : the current node. pointer to the current node.
 *
 * */
#define list_for_each_safe(pos, n, head) \
	for(pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)


/*
 * @brief : this macro is used to iterate over the list and get the entry of the list using the member
 * it will run as long as the pos is not equal to the head of the list.
 *
 * @param : pos : pointer to the current node.
 * @param : head : pointer to the head of the list.
 * @param : member : the member of the structure.
 * @param : type : the type of the structure that contains the member.
 *
 * @return : the current node. pointer to the current node.
 * */
#define list_for_each_entry(pos, head, member) \
	for(pos = list_entry((head)->next, typeof(*pos), member); \
		&pos->member != (head); \
		pos = list_entry(pos->member.next, typeof(*pos), member))


/*
 * @brief : this macro is used to iterate over the list using the member and copy the current node pointer to the next node
 * it will run as long as the pos is not equal to the head of the list.
 * this macro is used to prevent the deletion of the current node.
 *
 * @param : pos : pointer to the current node.
 * @param : n : pointer to the next node.
 * @param : head : pointer to the head of the list.
 * @param : member : the member of the structure.
 *
 * @return : the current node. pointer to the current node.
 * */
#define list_for_each_entry_safe(pos, n, head, member) \
	for(pos = list_entry((head)->next, typeof(*pos), member), \
		n = list_entry(pos->member.next, typeof(*pos), member); \
		&pos->member != (head); \
		pos = n, n = list_entry(n->member.next, typeof(*n), member))


/*
 * @brief : this macro is used to initialize the head of the list.
 * @param : name : the name of the list.
 *
 * */
#define LL_HEAD_INIT(name) { &(name), &(name) }

/*
 * @brief : this macro is used to initialize the list.
 * @param : name : the name of the list.
 *
 * */
#define LIST_INIT(name) struct ll_head name = LL_HEAD_INIT(name)

/*
 * @brief : this function is used to insert a new node into the list.
 * @param : new : pointer to the new node.
 * @param : prev : pointer to the previous node.
 * @param : next : pointer to the next node.
 *
 * */
static inline void list_insert(struct ll_head *new, struct ll_head *prev, struct ll_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}


/*
 * @brief : this function is used to add a new node to the list.
 * @param : new : pointer to the new node.
 * @param : head : pointer to the head of the list.
 *
 * */
static inline void list_add(struct ll_head *new, struct ll_head *head)
{
	list_insert(new, head, head->next);
}
/*
 * @brief : this function is used to add a new node to the end of the list.
 * @param : new : pointer to the new node.
 * @param : head : pointer to the head of the list.
 *
 * */
static void inline list_add_tail(struct ll_head *new, struct ll_head *head)
{
	list_insert(new, head->prev, head);
}


/*
 * @brief : this function is used to delete a node from the list.
 * @param : entry : pointer to the node that we want to delete.
 *
 * */
static inline void list_del(struct ll_head *entry)
{
	struct ll_head *prev = entry->prev;
	struct ll_head *next = entry->next;
	next->prev = prev;
	prev->next = next;
	entry->next = entry->prev = NULL;
}

/*
 * by default the decl specifiers are static , if you want to change it to extern , you can define the macro FREELIST_DECL_SPECIFIERS to be extern, otherwise it will be static.
 * it's static so that can't be accessed from outside the file.
 *
 * */
#ifndef FREELIST_DECL_SPECIFIERS
#define FREELIST_DECL_SPECIFIERS static
#endif

//header structure
/*
 * this is a container for the memory block , it contains the size of the block , a flag to indicate if the block is free or not
 * and a pointer to the next block in the list.
 * the size of the block is the size of the memory block + the size of the header.
 * Header structure , I put it as a union to guarntees that the header of the block is aligned .
   End of the header is the actual memory block begins .
*/


typedef struct{
        char *block;
        LinkedList_t node;
	size_t size;
				//to check if the block is free or not
	bool free;
}node_alloc_t;
        
//macro for making sure that the header is aligned to the nearest power of two
#define align_up(num, align) (((num) + ((align) - 1)) & ~((align) - 1))                               

//providing the memory address , to translate it to the header address
#define ALLOC_HEADER_SIZE offsetof(node_alloc_t, block)

#define MIN_ALLOC_SIZE (ALLOC_HEADER_SIZE + 32)
#define MAX_ALLOC_SIZE (1024 * 1024 * 1024 *1024)


//this macro is used to check if the multiplication of two numbers will overflow or not
//if it's overflowed , it will return 1 , otherwise it will return 0
//used in calloc() function
#define MUL_NO_OVERFLOW (1UL << (sizeof(size_t) * 4))

/*
 * flag used in malloc() function to cause competing threads to wait until intialization is done before allocating memory.
 * this is a flag to indicate if the memory is initialized or not.
 * if it's not initialized , we have to initialize it.
 * if it's initialized , we don't have to initialize it again.
*/
static volatile bool initialized = false;


/*
 basic locking mechanism ,to prevent that two or more threads accessing the memory at the same time
 before every action on memory ,we have to aquire the lock and once we done we have to release it.
 *
 * Example: malloc() calls will aquire the lock , and once it's done it will release it.
 * 		so malloc will be the only function that will be executed at a time.
*/
pthread_mutex_t malloc_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for thread safety


//functions prototypes

void malloc_add_block(void *block, size_t size);
void *malloc(size_t size);
void free(void *block);
void *calloc(size_t num, size_t nsize);
void* realloc(void* ptr, size_t size);

#endif /* BASIC_MANAGEMENT_H_ */

