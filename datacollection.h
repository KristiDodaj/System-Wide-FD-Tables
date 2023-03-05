
// datacollection.h: This is a header file responsible for defining the contents of the process data structure as well as the function signature of getProcesses(process **processes)

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