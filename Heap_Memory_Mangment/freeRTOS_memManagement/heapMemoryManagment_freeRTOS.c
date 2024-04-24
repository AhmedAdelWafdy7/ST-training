/*
    * heapMemoryManagment_freeRTOS.c
    *
    *  Created on: 15-Apr-2024
    * 
    * Author: Ahmed Adel Wafdy | WAFDUNIX

*/

#include "heapMemoryManagment_freeRTOS.h"


/*
 * @brief: add a heap region to the heap regions table 
 * 
 * @param: pvHeapStart: the start address of the heap region
 * @param: xHeapSize: the size of the heap region
 * 
 * @return: void
 * 
 * NOTE: This function will add the heap region to the heap regions table , we won't sort the heap regions table when adding a new heap region 
 * isntead we will sort prior to initializing the heap memory , this is to avoid sorting the heap regions table multiple times.
*/
void malloc_addHeapRegion(void *pvHeapStart, size_t xHeapSize){
    assert(pvHeapStart &&(xHeapSize > 0 )); // check if the heap start address is not null and the heap size is greater than 0
    assert((heapRegionsCnt < heapRegionsMax) && "TOO many heap regions"); // check if the heap regions count is less than the max heap regions count

    // increment the heap regions count
    uint8_t count = heapRegionsCnt++;

    if(count < heapRegionsMax){
        // add the heap region to the heap regions table
        xHeapRegions[count].pucStartAddress = pvHeapStart;
        xHeapRegions[count].xSizeInBytes = xHeapSize;
    }
    else{
        // if the heap regions count is greater than the max heap regions count
        // then we will not add the heap region to the heap regions table
        // and we will decrement the heap regions count
        heapRegionsCnt--;

    }
}

/**
 * @brief: initialize the heap memory
 * 
 * @return: void
 * 
 * NOTE: This function will sort the heap regions table and pass it to FreeRTOS to use the heap regions
*/
void malloc_init(void){
    assert((heapRegionsCnt > 0) && !heapInitialized); // check if the heap regions count is greater than 0 and the heap is not initialized
    if(heapRegionsCnt > 0  && !heapInitialized){
        // sort the heap regions table
        qsort(xHeapRegions, heapRegionsCnt, sizeof(HeapRegion_t), cmp_heapRegions);
        
        //pass the array into vPortDefineHeapRegions() to enable FreeRTOS to use the heap regions
        vPortDefineHeapRegions(xHeapRegions);

        // set the heap initialized flag to true
        heapInitialized = true;
    }
}

/**
 * @brief: compare two heap regions
 * 
 * @param: a: the first heap region
 * @param: b: the second heap region
 * 
 * @return: -1 if the start address of the first heap region is less than the start address of the second heap region
 *         1 if the start address of the first heap region is greater than the start address of the second heap region
 *        0 if the start address of the first heap region is equal to the start address of the second heap region
 * 
 * NOTE: This function is used to allow us to access and compare the heap regions
*/
static int cmp_heapRegions(const void *a, const void *b){
    const HeapRegion_t *x = a;
    const HeapRegion_t *y = b;
// compare the start address of the heap regions
// if the start address of the first heap region is less than the start address of the second heap region
// then return -1
// if the start address of the first heap region is greater than the start address of the second heap region
// then return 1
    return (x->pucStartAddress < y->pucStartAddress) ? -1 : (x->pucStartAddress > y->pucStartAddress);
}

/**
 * @brief: allocate memory
 * 
 * @param: xWantedSize: the size of the wanted memory
 * 
 * @return: a pointer to the allocated memory
 * 
 * NOTE: This function will allocate memory using FreeRTOS pvPortMalloc() function
*/
void *malloc(size_t xWantedSize){
    void *ptr = NULL;

    while(!heapInitialized){ 
        // wait until the heap is initialized
        vTaskDelay(1);
    }

    if(xWantedSize > 0){
        // allocate memory
        ptr = pvPortMalloc(xWantedSize);
    } // if the wanted size is less than or equal to 0 then return NULL

    return ptr;
}

/**
 * @brief: free memory
 * 
 * @param: ptr: the pointer to the memory to be freed
 * 
 * @return: void
 * 
 * NOTE: This function will free the memory using FreeRTOS vPortFree() function
*/
void free(void *ptr){

    assert(heapInitialized); // check if the heap is initialized
    if(ptr){
        // free the memory
        vPortFree(ptr);
    }
}