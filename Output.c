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
    // This function will take in the array process **processes along with its length size_t count and create a composite table.
    // Additionally, the function will recieve the long int pid which will be equal to -1 if we want to go through every process,
    // or equal to a particular pid if we want to generate a composite table for a specific process.
    // Note: The composite table is composed of (PID, FD, Filename, Inode) info

    // print header
    printf("\n%-6s%-10s%-10s%-30s\t%-10s\n", " ", "PID", "FD", "Filename", "Inode");
    printf("%-6s======================================================================\n", " ");

    // print content
    for (size_t i = 0; i < count; i++)
    {
        if (pid == -1)
        {
            printf("%-6s%-10ld%-10ld%-30s\t%-10ld\n", " ", (*processes + i)->pid, (*processes + i)->fd, (*processes + i)->filename, (*processes + i)->inode);
        }
        else
        {
            if ((*processes + i)->pid == pid)
            {
                printf("%-6s%-10ld%-10ld%-30s\t%-10ld\n", " ", (*processes + i)->pid, (*processes + i)->fd, (*processes + i)->filename, (*processes + i)->inode);
            }
        }
    }

    printf("%-6s======================================================================\n\n", " ");
}

void getPerProcess(process **processes, size_t count, long int pid)
{
    // This function will take in the array process **processes along with its length size_t count and create a per process table.
    // Additionally, the function will recieve the long int pid which will be equal to -1 if we want to go through every process,
    // or equal to a particular pid if we want to generate a per process table for a specific process.
    // Note: The per process table is composed of (PID, FD) info

    // print header
    printf("\n%-6s%-10s%-10s\n", " ", "PID", "FD");
    printf("%-6s===============\n", " ");

    // print content
    for (size_t i = 0; i < count; i++)
    {
        if (pid == -1)
        {
            printf("%-6s%-10ld%-10ld\n", " ", (*processes + i)->pid, (*processes + i)->fd);
        }
        else
        {
            if ((*processes + i)->pid == pid)
            {
                printf("%-6s%-10ld%-10ld\n", " ", (*processes + i)->pid, (*processes + i)->fd);
            }
        }
    }
    printf("%-6s===============\n\n", " ");
}

void getSystemWide(process **processes, size_t count, long int pid)
{
    // This function will take in the array process **processes along with its length size_t count and create a system-wide FD table.
    // Additionally, the function will recieve the long int pid which will be equal to -1 if we want to go through every process,
    // or equal to a particular pid if we want to generate a system-wide FD table for a specific process.
    // Note: The system-wide FD table is composed of (PID, FD, Filename) info

    // print header
    printf("\n%-6s%-10s%-10s%-30s\n", " ", "PID", "FD", "Filename");
    printf("%-6s==================================================\n", " ");

    // print content
    for (size_t i = 0; i < count; i++)
    {
        if (pid == -1)
        {
            printf("%-6s%-10ld%-10ld%-30s\n", " ", (*processes + i)->pid, (*processes + i)->fd, (*processes + i)->filename);
        }
        else
        {
            if ((*processes + i)->pid == pid)
            {
                printf("%-6s%-10ld%-10ld%-30s\n", " ", (*processes + i)->pid, (*processes + i)->fd, (*processes + i)->filename);
            }
        }
    }
    printf("%-6s==================================================\n\n", " ");
}

void getVnodes(process **processes, size_t count, long int pid)
{
    // This function will take in the array process **processes along with its length size_t count and create a Vnodes FD table .
    // Additionally, the function will recieve the long int pid which will be equal to -1 if we want to go through every process,
    // or equal to a particular pid if we want to generate a Vnodes FD table for a specific process.
    // Note: The Vnodes FD table is composed of (FD, Inode) info

    // print header
    printf("\n%-6s%-10s%-15s\n", " ", "FD", "Inode");
    printf("%-6s=================================\n", " ");

    // print content
    for (size_t i = 0; i < count; i++)
    {
        if (pid == -1)
        {
            printf("%-6s%-10ld%-15ld\n", " ", (*processes + i)->fd, (*processes + i)->inode);
        }
        else
        {
            if ((*processes + i)->pid == pid)
            {
                printf("%-6s%-10ld%-15ld\n", " ", (*processes + i)->fd, (*processes + i)->inode);
            }
        }
    }
    printf("%-6s=================================\n\n", " ");
}

bool pidAccounted(long int pids[], size_t count, long int pid)
{

    for (size_t i = 0; i < count; i++)
    {
        if (pids[i] == pid)
        {
            return true;
        }
    }
    return false;
}

void getOffending(process **processes, size_t count, long int threshhold)
{
    // initialize an array that will store all the unique pids
    long int pids[count];

    for (size_t i = 0; i < count; i++)
    {
        pids[i] = -1;
    }

    // populate array with the unique pids
    int number_of_pids = 0;
    for (size_t i = 0; i < count; i++)
    {
        if (pidAccounted(pids, count, (*processes + i)->pid) == false)
        {
            pids[i] = (*processes + i)->pid;
            number_of_pids += 1;
        }
    }

    // store number of FD for each processes
    long int fd_num[count];

    for (size_t i = 0; i < count; i++)
    {
        if (pids[i] == -1)
        {
            fd_num[i] = -1;
        }
        else
        {
            long int fds = 0;

            for (size_t i = 0; i < count; i++)
            {
                if ((*processes + i)->pid == pids[i])
                {
                    fds += 1;
                }
            }

            fd_num[i] = fds;
        }
    }

    // print offending output
    printf("\n## Offending processes:\n");

    for (size_t i = 0; i < count; i++)
    {
        if (fd_num[i] > threshhold && fd_num[i] != -1)
        {
            printf("%ld (%ld), ", pids[i], fd_num[i]);
        }
    }
}

int main()
{
    process **processes = (process **)malloc(sizeof(process *));
    size_t count = getProcesses(processes);
    getCompositeTable(processes, count, -1);
    getOffending(processes, count, 20);
}
