# Wafdunix Picoshell

Wafdunix Picoshell is a simple Unix shell implementation consisting of three main files: `main.c`, `utilities.c`, and `utilities.h`. This minimalistic shell provides basic functionalities such as executing commands, changing directories, copying files, moving files, echoing input, and printing the current working directory.

## File Descriptions

### utilities.h

```c
/* -------------------- includes------------------------ */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

/*-----------------------------macro functions declaration------------------------------*/
#define clear() printf("\033[H\033[J")

/* ------------------------------Data Types Declaration ------------------------------- */
int x, result;
char buf[100];
int read_count;
char *argv[] = { NULL };

/*------------------------------functions declaration-------------------------*/
void initialize_shell(void);
void getInput(char buf[100]);
void printDir(void);
void echo(char buf[100]);
void execute_command(char *args[]);
```

### utilities.c

```c
#include "utilities.h"

void execute_command(char *args[]) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
    } else if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror("execvp"); // If execvp fails
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}
```

### main.c

```c
#include "utilities.h"

int argc = 0;
char buf[100];

int main() {
    initialize_shell();

    while (1) {
        printf("\nAhmedfandes shell>>> ");
        fgets(buf, 100, stdin);
        int len = strlen(buf);
        buf[len - 1] = 0;
        getInput(buf);

        if (strcmp(argv[0], "exit") == 0) {
            printf("Good bye :)\n$");
            break; // breaking the shell
        } else if (strcmp(argv[0], "cd") == 0) {
            chdir(argv[1]);
        } else if (strcmp(argv[0], "cp") == 0) {
            // ... (copy functionality)
        } else if (strcmp(argv[0], "mv") == 0) {
            // ... (move functionality)
        } else if (strcmp(argv[0], "echo") == 0) {
            // ... (echo functionality)
        } else if (strcmp(argv[0], "pwd") == 0) {
            printDir();
        } else {
            execute_command(argv);
        }
    }
}
```

## How to Use

1. Clone the repository or download the files.
2. Compile the code using a C compiler (e.g., `gcc`).
3. Run the compiled executable.

## Features

- Basic shell commands: `cd`, `cp`, `mv`, `echo`, `pwd`, and `exit`.
- Executes external commands using `execvp`.
- Supports basic input/output redirection.


https://github.com/AhmedAdelWafdy7/ST-training/assets/107740350/0213ed14-cb2f-4e39-bcea-b2eb9542f13a

