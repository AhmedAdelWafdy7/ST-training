## Heap Memory Management Library - README.md

This document provides instructions on using the provided Makefile to build and test your custom heap memory management library.

### Makefile Overview

The provided Makefile defines the following targets:

* **all:** This is a convenience target that calls `clean` and `compile` sequentially.
* **clean:** Removes all object files (`.o`), static library (`.a`), and shared library (`.so`) generated during compilation.
* **compile:**
    * Compiles the `basic_mangement.c` source file with static linking, creating object files.
    * Creates the static library `liballoc.a` from the object files.
    * Compiles the `basic_mangement.c` source file with dynamic linking, creating the shared library `liballoc.so`.
* **test:**
    * Sets the `LD_PRELOAD` environment variable to point to the `liballoc.so` library.
    * Provides instructions on running your programs to test the library.
    * Suggests testing various commands like `gdb`, `vim`, `nano`, `ls`, `cat`, `echo`, etc.
* **linux:**
    * Similar to `compile`, but specifically builds the library for Linux environments.

### Usage

1. **Build the library:**

   ```bash
   make all
   ```

2. **Test the library:**

   ```bash
   make test
   ```

   This will set the `LD_PRELOAD` environment variable to use your custom library and then prompt you to run your programs. You can test various commands to see how they interact with your library's memory management functions.

