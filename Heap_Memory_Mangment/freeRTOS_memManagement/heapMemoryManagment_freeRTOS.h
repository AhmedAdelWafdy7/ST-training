/*
    * heapMemoryManagment_freeRTOS.h
    *
    *  Created on: 15-Apr-2024
    * 
    * Author: Ahmed Adel Wafdy | WAFDUNIX
    * NOTE: This FreeRTOS malloc implementation requires heap_5.c to be used in FreeRTOSConfig.h
*/

#ifndef HEAPMEMORYMANAGMENT_FREERTOS_H_
#define HEAPMEMORYMANAGMENT_FREERTOS_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// FreeRTOS Heap Memory Management
// we want to manage an internal HeapRegion_t array to keep track of the allocated memory
//we will create a max limit for heap regions
#ifndef MAX_HEAP_REGIONS_CNT
#define MAX_HEAP_REGIONS_CNT 2
#endif

// HeapRegion_t table needs to be NULL terminated ,so we allocate one extra element to ensure that the last element is NULL.
static HeapRegion_t xHeapRegions[MAX_HEAP_REGIONS_CNT + 1] = {0};

// create a variable representing the number of heap regions
static const uint8_t heapRegionsMax = MAX_HEAP_REGIONS_CNT;

// create a variable to track the current number of entries in the heap region table
static volatile uint8_t heapRegionsCnt = 0;


// boolean to check if the heap is initialized
static bool heapInitialized = false;


//********************************************************************************************************************
// Function Prototypes
void malloc_addHeapRegion(void *pvHeapStart, size_t xHeapSize);

void malloc_init(void);

static int cmp_heapRegions(const void *a, const void *b);

void *malloc(size_t xWantedSize);

void free(void *ptr);



#endif /* HEAPMEMORYMANAGMENT_FREERTOS_H_ */