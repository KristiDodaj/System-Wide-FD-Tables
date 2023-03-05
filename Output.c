#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "datacollection.h"

bool pidExists(process **processes, size_t count, long int pid)
{
    // This function will take in the array process **processes along with its length size_t count and a pid number and will check
    // whether that pid exists in the array. The function will return true if it exists and false if it does not.

    // iterate array and find pid
    for (size_t i = 0; i < count; i++)
    {
        if ((*processes + i)->pid == pid)
        {
            return true;
        }
    }
    return false;
}

void getCompositeTable(process **processes, size_t count, long int pid)
{
    // This function will take in the array process **processes along with its length size_t count and create a composite table. Additioanally, the function will recieve the long int pid which will be equal to -1 if
    // we want to go through every process, or equal to a particular pid if we want to generate a composite table for a specific process.
    // Note: The composite table is composed of (PID, FD, Filename, Inode) info

    // print header
    printf("\n%-6s%-10s%-10s%-20s\t\t%-10s\n", " ", "PID", "FD", "Filename", "Inode");
    printf("%-6s==============================================================\n", " ");

    // print content
    long int counter = 0;

    for (size_t i = 0; i < count; i++)
    {
        if (pid == -1)
        {
            printf("%-6s%-10ld%-10ld%-20s%-10ld\n", " ", (*processes + i)->pid, (*processes + i)->fd, (*processes + i)->filename, (*processes + i)->inode);
        }
        else
        {
            if ((*processes + i)->pid == pid)
            {
                printf("%-6s%-10ld%-10ld%-20s%-10ld\n", " ", (*processes + i)->pid, (*processes + i)->fd, (*processes + i)->filename, (*processes + i)->inode);
                counter++;
            }
        }
    }

    printf("%-6s==============================================================\n", " ");
}

void getPerProcess(process **processes, size_t count, long int pid)
{
    // This function will take in the array process **processes along with its length size_t count and create a per process table. Additioanally, the function will recieve the long int pid which will be equal to -1 if
    // we want to go through every process, or equal to a particular pid if we want to generate a per process table for a specific process.
    // Note: The per process table is composed of (PID, FD) info

    // print header
    printf("\n%-6s%-10s%-10s\n", " ", "PID", "FD");
    printf("%-6s===========================================\n", " ");

    // print content
    long int counter = 0;

    for (size_t i = 0; i < count; i++)
    {
        if (pid == -1)
        {
            printf("%-6s%-10ld%-10ld", " ", (*processes + i)->pid, (*processes + i)->fd);
        }
        else
        {
            if ((*processes + i)->pid == pid)
            {
                printf("%-6s%-10ld%-10ld", " ", (*processes + i)->pid, (*processes + i)->fd);
                counter++;
            }
        }
    }
    printf("%-6s==============================================================\n", " ");
}

int main()
{
    process **processes = (process **)malloc(sizeof(process *));
    size_t count = getProcesses(processes);
    getCompositeTable(processes, count, -1);
}
