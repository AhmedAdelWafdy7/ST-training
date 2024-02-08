# Wafdunix Picoshell


Welcome to Pico Shell! Pico Shell is a minimalistic shell implementation with built-in commands and support for memory allocation and redirection. It is designed to provide a lightweight and efficient command-line interface.

## Features

- **Built-in Commands**: Pico Shell includes several built-in commands for common file system operations and environment management. These commands include:
  - `ls`: List directory contents.
  - `cp`: Copy files and directories.
  - `cd`: Change the current directory.
  - `mv`: Move or rename files and directories.
  - `echo`: Display a line of text.
  - `pwd`: Print the current working directory.
  - `set`: Set environment variables.
  - `unset`: Unset environment variables.
  - `env`: Display or modify environment variables.
  - `mkdir`: Create directories.
  - `rm`: Remove files or directories.
  
- **Memory Allocation**: Pico Shell supports memory allocation, enabling efficient handling of system resources and reducing memory leaks.

- **Redirection**: Pico Shell supports input and output redirection, allowing users to control where the input comes from and where the output goes.

## Implementation Details

All built-in commands are implemented in `utilities.h`, providing a simple and efficient way to perform common tasks within the shell.

## Usage

To use Pico Shell, simply compile the source code and run the executable. Once launched, you can use the built-in commands as described above. 

Here's a basic example:

```bash
$ ./picoshell
Pico Shell started.
$ ls
file1.txt file2.txt directory
$ cp file1.txt file3.txt
$ ls
file1.txt file2.txt file3.txt directory
$ cd directory
$ pwd
/home/user/directory
```

## Dependencies

Pico Shell has minimal dependencies and should run on most Unix-like systems.
