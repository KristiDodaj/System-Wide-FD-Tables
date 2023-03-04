#ifndef DATA
#define DATA

#include <stddef.h> // Include the header file that defines size_t

// Define a CDT that represents a single process including it's information (pid, fd, filename, inode)

typedef struct
{
    long int pid;
    long int fd;
    char *filename;
    long int inode;
} process;

// define the function getProcesses()
size_t getProcesses(process **processes);

#endif /* DATA */