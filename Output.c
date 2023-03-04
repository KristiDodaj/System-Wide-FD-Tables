#include <stdlib.h>
#include <stdio.h>
#include "datacollection.h"

void getCompositeTable(process **processes, size_t count, long int pid)
{
    // This function will take in the array process **processes along with its length size_t count. Additioanally, the function will recieve the long int pid which will be equal to -1 if
    // we want to go through every process, or equal to a particular pid if we want to generate a composite table for a specific process.

    // print header
    printf("PID\tFD\tFilename\t\tInode\n");
    printf("===============================================\n");

    for (size_t i = 0; i < count; i++)
    {
        if (pid == -1)
        {
            printf("%ld\t%ld\t%s\t\t%lu\n", (*processes + i)->pid, (*processes + i)->fd, (*processes + i)->filename, (*processes + i)->inode);
        }
    }
}

int main()
{

    process **processes = (process **)malloc(sizeof(process *));
    size_t count = getProcesses(processes);
    getCompositeTable(processes, count, -1);
}
