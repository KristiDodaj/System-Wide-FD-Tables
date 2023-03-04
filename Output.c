#include <stdlib.h>
#include <stdio.h>
#include "datacollection.h"

void getCompositeTable(process **processes, size_t count, long int pid)
{
    // This function will take in the array process **processes along with its length size_t count. Additioanally, the function will recieve the long int pid which will be equal to -1 if
    // we want to go through every process, or equal to a particular pid if we want to generate a composite table for a specific process.
    // Note: The composite table is composed of (PID, FD, Filename, Inode) info

    // print header
    printf("%-10s%-10s%-30s%-10s\n", "PID", "FD", "Filename", "Inode");
    printf("===============================================\n");

    for (size_t i = 0; i < count; i++)
    {
        if (pid == -1)
        {
            printf("%-10ld%-10ld%-30s%-10ld\n", (*processes + i)->pid, (*processes + i)->fd, (*processes + i)->filename, (*processes + i)->inode);
        }
    }
}

int main()
{

    process **processes = (process **)malloc(sizeof(process *));
    size_t count = getProcesses(processes);
    getCompositeTable(processes, count, -1);
}
