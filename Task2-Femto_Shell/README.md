# WAFDUNIX Shell

WAFDUNIX Shell is a simple Unix-like shell implemented in C, allowing users to enter commands and execute them. This README.md file provides an overview of the code structure and functionalities.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Functions](#functions)

## Introduction

WAFDUNIX Shell is a basic command-line shell that initializes and prompts the user for commands. It takes input, parses it, and then executes the corresponding actions. The shell will continue running until the user inputs the "exit" command.

## Features

- User-friendly prompt.
- Basic command parsing.
- Execution of commands.
- Graceful exit with the "exit" command.

## Usage

To use the WAFDUNIX Shell, simply compile the C code and run the executable. The shell will prompt the user to enter commands, and it will execute them accordingly. To exit the shell, type "exit."

```bash
$ gcc wafdunix_shell.c -o wafdunix_shell
$ ./wafdunix_shell
```

## Functions

### `initialize_shell()`

This function initializes the WAFDUNIX Shell, displaying a welcome message and clearing the terminal screen.

### `getInput(char buf[100])`

This function takes user input as a string (`buf`) and tokenizes it using space as the delimiter. The tokens are stored in the `argv` array for further processing.

### `main()`

The main function of the WAFDUNIX Shell. It calls `initialize_shell()` to set up the shell, then enters a loop to continuously prompt the user for input. It uses `getInput()` to parse the input and checks for the "exit" command to terminate the shell.
