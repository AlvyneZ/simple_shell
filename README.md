# Simple Shell
## Authors: AlvyneZ & Mwogoi
This repository contains C program source code for implementing a simple shell in C  
\
### execve
The shell implementation is built around the execve (execute program) system call.  
\
SYNOPSIS:  
```
#include <unistd.h>  
int execve(const char *pathname, char *const argv[], char *const envp[]);  
```
\
The execve system call causes the program that is currently being run by the calling process to be replaced with a new program, with newly initialized stack, heap, and (initialized and uninitialized) data segments.  
\
### fork
In order to prevent the simple shell program from being overwritten by the program executed by execve, the fork system call is needed to make a child process that will be the one to be overwritten; leaving the shell program running.  
\
SYNOPSIS:  
```
#include <sys/types.h>
#include <unistd.h>
pid_t fork(void);
```
\
The fork system call creates a new process by duplicating the calling process.  The new process (child process) has a separate memory space from the calling process (parent process).  
The parent and child processes have different process identifiers (pid), but the pid returned by the fork call is 0 in the child and equal to the child pid in the parent.  
\
### isatty
In order to know whether the program is to be run in interactive mode the input and output streams need to be terminal/tty. The isatty system call is used to file descriptors.  
\
SYNOPSIS:  
```
#include <unistd.h>
int isatty(int fd);
```
\
### getline
This is used to read an entire line from the input stream, storing the address of the buffer containing the text into a buffer. If a NULL buffer pointer is provided to the system call, a buffer will be allocated. This buffer should be freed by the user program even if getline() failed.  
\
SYNOPSIS:  
```
#include <stdio.h>
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
```
\