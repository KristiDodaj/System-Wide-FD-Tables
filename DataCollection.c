#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// This CDT represents a single process including it's information (pid, fd, filename, inode)

typedef struct
{
    char *pid;
    char *fd;
    char *filename;
    long int inode;
} process;

// This function will populate a dynamic array with the process data strcutures defined above.

void getProcesses()
{

    // open the /proc directory
    DIR *directory = opendir("/proc");

    // check if sucessfully opened
    if (directory == NULL)
    {
        perror("Opening /proc directory failed");
    }

    // go through the directory entries
    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL)
    {

        // validate that the entry is a directory that is a PID
        if (atoi(entry->d_name) == 0)
        {
            printf("PID: %s\n", entry->d_name);
        }
    }
    closedir(directory);
}

int main()
{
    getProcesses();
    return 0;
}