## README.md for heapMemoryManagment_freeRTOS.h and heapMemoryManagment_freeRTOS.c

This document provides an overview of the `heapMemoryManagment_freeRTOS.h` and `heapMemoryManagment_freeRTOS.c` files, which implement a custom heap memory management system for FreeRTOS.

### Overview

These files provide functions for managing multiple heap regions within FreeRTOS. This allows for more granular control over memory allocation within specific memory areas.

### Key Features

* **Multiple Heap Regions:** Supports managing up to `MAX_HEAP_REGIONS_CNT` separate heap regions.
* **Heap Initialization:** Requires explicit initialization using `malloc_init()` to sort and configure the heap regions for FreeRTOS usage.
* **Memory Allocation:** Provides `malloc()` function for allocating memory from the managed heap regions.
* **Memory Freeing:** Provides `free()` function for freeing memory previously allocated using `malloc()`.
* **FreeRTOS Integration:** Leverages FreeRTOS's `pvPortMalloc()` and `vPortFree()` functions for memory allocation and deallocation.

### File Structure

* **heapMemoryManagment_freeRTOS.h:**
    * Declares header information for the heap management functions.
    * Defines data structures and constants related to heap regions.
    * Declares function prototypes for:
        * `malloc_addHeapRegion`: Adds a new heap region to the management system.
        * `malloc_init`: Initializes the heap management system.
        * `cmp_heapRegions`: Compares two heap regions based on their start addresses.
        * `malloc`: Allocates memory from the managed heap regions.
        * `free`: Frees memory previously allocated using `malloc`.
* **heapMemoryManagment_freeRTOS.c:**
    * Provides implementations for the functions declared in `heapMemoryManagment_freeRTOS.h`.

### Usage

1. Include `heapMemoryManagment_freeRTOS.h` in your application files.
2. Define `MAX_HEAP_REGIONS_CNT` in your FreeRTOS configuration (e.g., `FreeRTOSConfig.h`) to specify the maximum number of heap regions.
3. Call `malloc_addHeapRegion` for each heap region you want to manage, providing the start address and size.
4. Call `malloc_init` to initialize the heap management system after adding all heap regions.
5. Use `malloc` to allocate memory from the managed heap regions.
6. Use `free` to release memory previously allocated using `malloc`.

**Important Notes:**

* Ensure `heap_5.c` is included in your FreeRTOS configuration (`FreeRTOSConfig.h`) for this custom heap management implementation to work correctly.
* The heap regions table is sorted before initialization to optimize memory allocation efficiency.
* Memory allocation and deallocation are performed using FreeRTOS's internal functions (`pvPortMalloc` and `vPortFree`).
