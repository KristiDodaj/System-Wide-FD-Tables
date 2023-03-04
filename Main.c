#include <stdlib.h>
#include <stdio.h>
#include "datacollection.h"

int main()
{

    process **processes = (process **)malloc(sizeof(process *));
    size_t count = getProcesses(processes);

    printf("================================\n");

    for (size_t i = 0; i < count; i++)
    {
        printf("%-10ld %-10ld %-50s %lu\n", (*processes + i)->pid, (*processes + i)->fd, (*processes + i)->filename, (*processes + i)->inode);
    }
}
