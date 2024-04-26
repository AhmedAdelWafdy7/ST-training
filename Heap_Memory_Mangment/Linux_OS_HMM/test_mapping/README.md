## Exploring Lazy Allocation in Linux User Space

This document demonstrates the concept of lazy allocation in Linux user space, where physical memory is only mapped when accessed by a program. 

### Lazy Allocation Explained

Linux employs a memory management technique called lazy allocation for user space. This means that when a program allocates memory using functions like `malloc(3)`, it receives a pointer to a block of memory addresses, but no actual physical memory is initially assigned. Instead, a flag is set in the page table entries, indicating that any read or write access to this memory will trigger a page fault.

**Page Fault:** This is a trap to the kernel that occurs when a program attempts to access a memory address that is not currently mapped to physical memory.

**Kernel Intervention:** Only at the point of a page fault does the kernel take action. It finds a free page of physical memory and adds it to the page table mapping for the process, allowing the program to proceed with its memory access.

### Demonstration Program

This repository contains a simple program that demonstrates lazy allocation and page faults. 

### Observations

Running the program reveals the following:

* **Minor Page Faults:** 
    * 80 minor page faults occurred during program initialization.
    * 4 additional minor page faults occurred when calling `getrusage(2)`.
    * These numbers vary depending on the architecture and C library version.
* **Memory Buffer:** 
    * 340 - 84 = 256 The program allocates a 1 MiB buffer, which translates to 256 pages.
    * During the process of filling the buffer with data, 256 minor page faults were encountered.

### Beyond Page Faults: Memory Map

While `getrusage(2)` offers insights into minor and major page faults, a complete picture requires a detailed memory map of the process. 

![Benwafdy  Running  - Oracle VM VirtualBox 4_26_2024 4_48_35 AM](https://github.com/AhmedAdelWafdy7/ST-training/assets/107740350/13b7ce4f-0154-4c90-ab1f-98538921aecd)

This repository does not currently include a tool for generating a memory map, but it provides a foundation for further exploration of this concept. 

