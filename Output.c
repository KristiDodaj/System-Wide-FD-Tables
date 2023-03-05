
// Output.c: This files is responsible for providing and defining the output given the set of command lines arguments

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "datacollection.h"

bool pidExists(process **processes, size_t count, long int pid)
{
    // This function will take in the array "process **processes" along with its length "size_t count" and a pid number (long int pid) and will check
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
    // This function will take in the array "process **processes" along with its length "size_t count" and create a composite table.
    // Additionally, the function will recieve the "long int pid" which will be equal to -1 if we want to go through every process,
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
    // This function will take in the array "process **processes" along with its length "size_t count" and create a per process table.
    // Additionally, the function will recieve the "long int pid" which will be equal to -1 if we want to go through every process,
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
    // This function will take in the array "process **processes" along with its length "size_t count" and create a system-wide FD table.
    // Additionally, the function will recieve the "long int pid" which will be equal to -1 if we want to go through every process,
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
    // This function will take in the array "process **processes" along with its length "size_t count" and create a Vnodes FD table.
    // Additionally, the function will recieve the "long int pid" which will be equal to -1 if we want to go through every process,
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
    // This function takes in tn array "long int pids[]" with its size "size_t count" as well as the pid "long int pid" that we
    // are searching for. The function will return true if the pid already exists in the array and false if it does not.

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
    // This function will take in the array "process **processes" along with its length "size_t count" as well as a threshhold "long int threshhold"
    // and will print all the offending process in the format PID (FD), where FD represents the total number of fds for that process.
    // NOTES: We define an offending process as a process that has a number of file descriptors that exceeds the given threshhold.

    // initialize an array that will store all the unique pids
    long int pids[count];

    for (size_t i = 0; i < count; i++)
    {
        pids[i] = -1;
    }

    // populate array with the unique pidsßß
    for (size_t i = 0; i < count; i++)
    {
        if (pidAccounted(pids, count, (*processes + i)->pid) == false)
        {
            pids[i] = (*processes + i)->pid;
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

            for (size_t j = 0; j < count; j++)
            {
                if ((*processes + j)->pid == pids[i])
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
    printf("\n\n");
}

void outputText(process **processes, size_t count, long int pid)
{
    // This function will take in the array "process **processes" along with its length "size_t count" and create a composite table
    // that will be written in ASCII in a file named "compositeTable.txt".  Additionally, the function will recieve the "long int pid" which
    // will be equal to -1 if we want to go through every process, or equal to a particular pid if we want to generate a composite table for a specific process.
    // Note: The composite table is composed of (PID, FD, Filename, Inode) info

    // create the file
    FILE *file;
    file = fopen("compositeTable.txt", "w");

    if (file == NULL)
    {
        printf("Error creating file");
    }
    else
    {
        // print header
        fprintf(file, "\n%-6s%-10s%-10s%-30s\t%-10s\n", " ", "PID", "FD", "Filename", "Inode");
        fprintf(file, "%-6s======================================================================\n", " ");

        // print content
        for (size_t i = 0; i < count; i++)
        {
            if (pid == -1)
            {
                fprintf(file, "%-6s%-10ld%-10ld%-30s\t%-10ld\n", " ", (*processes + i)->pid, (*processes + i)->fd, (*processes + i)->filename, (*processes + i)->inode);
            }
            else
            {
                if ((*processes + i)->pid == pid)
                {
                    fprintf(file, "%-6s%-10ld%-10ld%-30s\t%-10ld\n", " ", (*processes + i)->pid, (*processes + i)->fd, (*processes + i)->filename, (*processes + i)->inode);
                }
            }
        }

        fprintf(file, "%-6s======================================================================\n\n", " ");
    }
    // close file
    fclose(file);
}

void outputBinary(process **processes, size_t count, long int pid)
{
    // This function will take in the array "process **processes" along with its length "size_t count" and create a composite table
    // that will be written in binary in a file named "compositeTable.bin".  Additionally, the function will recieve the "long int pid" which
    // will be equal to -1 if we want to go through every process, or equal to a particular pid if we want to generate a composite table for a specific process.
    // Note: The composite table is composed of (PID, FD, Filename, Inode) info

    // create the file
    FILE *file;
    file = fopen("compositeTable.bin", "wb");

    if (file == NULL)
    {
        printf("Error creating file");
    }
    else
    {
        // format header into character array
        char header[200];
        sprintf(header, "\n%-6s%-10s%-10s%-30s\t%-10s\n%-6s======================================================================\n", " ", "PID", "FD", "Filename", "Inode", " ");

        // write header to file
        fwrite(header, sizeof(char), strlen(header), file);

        // write content to file
        for (size_t i = 0; i < count; i++)
        {
            if (pid == -1)
            {
                fwrite(&((*processes + i)->pid), sizeof(long int), 1, file);
                fwrite(&((*processes + i)->fd), sizeof(long int), 1, file);
                fwrite((*processes + i)->filename, sizeof(char), strlen((*processes + i)->filename), file);
                fwrite(&((*processes + i)->inode), sizeof(long int), 1, file);
            }
            else
            {
                if ((*processes + i)->pid == pid)
                {
                    fwrite(&((*processes + i)->pid), sizeof(long int), 1, file);
                    fwrite(&((*processes + i)->fd), sizeof(long int), 1, file);
                    fwrite((*processes + i)->filename, sizeof(char), strlen((*processes + i)->filename), file);
                    fwrite(&((*processes + i)->inode), sizeof(long int), 1, file);
                }
            }
        }

        // format footer into character array
        char footer[100];
        sprintf(footer, "%-6s======================================================================\n\n", " ");

        // write footer to file
        fwrite(footer, sizeof(char), strlen(footer), file);
    }
    // close file
    fclose(file);
}

void parseArguments(int argc, char *argv[], bool *composite, bool *per_process, bool *system, bool *vnodes, int *threshold, long int *pid)
{
    // This function will take in int argc and char *argv[] and will update the boolean pointers (composite, per_process, system, vnodes) and int/long int
    // pointers (threshold, pid) according to the command line arguments inputted.

    for (int i = 0; i < argc; i++)
    {
        // find if --composite was called
        if (strcmp(argv[i], "--composite") == 0)
        {
            *composite = true;
        }
        // find if --per-process was called
        if (strcmp(argv[i], "--per-process") == 0)
        {
            *per_process = true;
        }
        // find if --systemWide was called
        if (strcmp(argv[i], "--systemWide") == 0)
        {
            *system = true;
        }
        // find if --Vnodes was called
        if (strcmp(argv[i], "--Vnodes") == 0)
        {
            *vnodes = true;
        }
        // check for flag --threshold
        int temp;
        if (sscanf(argv[i], "--samples=%d", &temp) == 1 && temp >= 0)
        {
            *threshold = temp;
        }
        // check for PID positional argument
        long int temp_pid;
        if (argc > 1)
        {
            if (sscanf(argv[1], "%d", &temp_pid) == 1)
            {
                *pid = temp_pid;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    process **processes = (process **)malloc(sizeof(process *));
    size_t count = getProcesses(processes);
    getOffending(processes, count, 0);
}
