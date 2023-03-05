
// Output.c: This files is responsible for providing and defining the output given the set of command lines arguments

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "datacollection.h"

bool pidExists(process **processes, size_t count, long int pid)
{
    // This function will take in the array "process **processes" along with its length "size_t count" and a pid number (long int pid) and will check
    // whether that pid exists in the array. The function will return true if it exists or is equal to -1 (indicating we want every pid) and false if it does not exist or is an invalid PID.
    // Example Output:
    // size_t count = 15
    // process **processes = {{ 118743, 0, "/dev/null", 5}, ........., {118743, 25, "socket:[642073]", 642073}} where ... represents the other 13 process structs
    // pidExists(processes, count, -23456)
    //
    // returns false and prints "THE INPUTTED PID IS IN THE WRONG FORMAT"
    // Example Output 2:
    // process **processes = {{ 118743, 0, "/dev/null", 5}, ........., {118743, 25, "socket:[642073]", 642073}} where ... represents the other 13 process structs
    // pidExists(processes, count, 118743)
    //
    // returns true

    // check it equals -1
    if (pid == -1)
    {
        return true;
    }

    // check if valid pid
    if (pid < -1)
    {
        printf("THE INPUTTED PID IS IN THE WRONG FORMAT");
        return false;
    }

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
    // Example Output:
    // getCompositeTable(process **processes, size_t count,  3391894) prints
    //
    //    PID       FD        Filename                      	Inode
    //  ======================================================================
    //  3391894   0         /dev/null                     	6
    //  3391894   1         socket:[1748824698]           	1748824698
    //  3391894   2         socket:[1748824698]           	1748824698
    //  3391894   3         socket:[1748838307]           	1748838307
    //  3391894   4         anon_inode:[eventpoll]        	10286
    //  3391894   5         anon_inode:[signalfd]         	10286
    //  3391894   6         anon_inode:inotify            	10286
    //  3391894   7         /sys/fs/cgroup/unified/user.slice/user-23629403.slice/user@23629403.service	256456
    //  3391894   8         anon_inode:[timerfd]          	10286
    //  3391894   9         anon_inode:[eventpoll]        	10286
    //  3391894   10        /proc/3391894/mountinfo       	1748838314
    //  3391894   11        anon_inode:inotify            	10286
    //  3391894   12        socket:[1748838341]           	1748838341
    //  3391894   13        anon_inode:inotify            	10286
    //  3391894   14        /proc/swaps                   	4026532071
    //  3391894   15        socket:[1748838315]           	1748838315
    //  3391894   16        socket:[1748838328]           	1748838328
    //  3391894   17        socket:[1748838329]           	1748838329
    //  3391894   18        socket:[1748838330]           	1748838330
    //  3391894   19        socket:[1748838331]           	1748838331
    //  3391894   20        socket:[1748838333]           	1748838333
    //  3391894   21        anon_inode:[timerfd]          	10286
    //  3391894   26        socket:[1748838346]           	1748838346
    //  3391894   27        socket:[1748838348]           	1748838348
    //  3391894   28        socket:[1748838350]           	1748838350
    //  3391894   29        socket:[1748838352]           	1748838352
    //  3391894   30        socket:[1748838354]           	1748838354
    //  3391894   31        socket:[1748838356]           	1748838356
    //  ======================================================================
    //
    // Similarily, it would print all the processes if the inputted pid is -1

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
    // Example Output:
    // getPerProcess(process **processes, size_t count, 3391894) prints
    //
    //  PID       FD
    //  ===============
    //  3391894   0
    //  3391894   1
    //  3391894   2
    //  3391894   3
    //  3391894   4
    //  3391894   5
    //  3391894   6
    //  3391894   7
    //  3391894   8
    //  3391894   9
    //  3391894   10
    //  3391894   11
    //  3391894   12
    //  3391894   13
    //  3391894   14
    //  3391894   15
    //  3391894   16
    //  3391894   17
    //  3391894   18
    //  3391894   19
    //  3391894   20
    //  3391894   21
    //  3391894   26
    //  3391894   27
    //  3391894   28
    //  3391894   29
    //  3391894   30
    //  3391894   31
    //  ===============
    //
    // Similarily, it would print all the processes if the inputted pid is -1

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
    // Example Output:
    // getSystemWide(process **processes, size_t count, 3391894) prints
    //
    // PID       FD        Filename
    //  ==================================================
    //  3391894   0         /dev/null
    //  3391894   1         socket:[1748824698]
    //  3391894   2         socket:[1748824698]
    //  3391894   3         socket:[1748838307]
    //  3391894   4         anon_inode:[eventpoll]
    //  3391894   5         anon_inode:[signalfd]
    //  3391894   6         anon_inode:inotify
    //  3391894   7         /sys/fs/cgroup/unified/user.slice/user-23629403.slice/user@23629403.service
    //  3391894   8         anon_inode:[timerfd]
    //  3391894   9         anon_inode:[eventpoll]
    //  3391894   10        /proc/3391894/mountinfo
    //  3391894   11        anon_inode:inotify
    //  3391894   12        socket:[1748838341]
    //  3391894   13        anon_inode:inotify
    //  3391894   14        /proc/swaps
    //  3391894   15        socket:[1748838315]
    //  3391894   16        socket:[1748838328]
    //  3391894   17        socket:[1748838329]
    //  3391894   18        socket:[1748838330]
    // 3391894   19        socket:[1748838331]
    //  3391894   20        socket:[1748838333]
    //  3391894   21        anon_inode:[timerfd]
    //  3391894   26        socket:[1748838346]
    //  3391894   27        socket:[1748838348]
    //  3391894   28        socket:[1748838350]
    //  3391894   29        socket:[1748838352]
    //  3391894   30        socket:[1748838354]
    //  3391894   31        socket:[1748838356]
    //  ==================================================
    //
    // Similarily, it would print all the processes if the inputted pid is -1

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
    // Example Output:
    // getVnodes(process **processes, size_t count, 3391894) prints
    //
    //  FD        Inode
    //  =================================
    //  0         6
    //  1         1748824698
    //  2         1748824698
    //  3         1748838307
    //  4         10286
    //  5         10286
    //  6         10286
    //  7         256456
    //  8         10286
    //  9         10286
    //  10        1748838314
    //  11        10286
    //  12        1748838341
    //  13        10286
    //  14        4026532071
    //  15        1748838315
    //  16        1748838328
    //  17        1748838329
    //  18        1748838330
    //  19        1748838331
    //  20        1748838333
    //  21        10286
    //  26        1748838346
    //  27        1748838348
    //  28        1748838350
    //  29        1748838352
    //  30        1748838354
    //  31        1748838356
    //  =================================
    //
    // Similarily, it would print all the processes if the inputted pid is -1

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
    // This function takes in the array "long int pids[]" with its size "size_t count" as well as the pid "long int pid" that we
    // are searching for. The function will return true if the pid already exists in the array and false if it does not.
    // Example Output:
    // long int pids[23, 645, 743];
    // pidAccounted(pids, 3, 743) returns
    //
    // true
    // Example Output 2:
    // long int pids[23, 645, 743];
    // pidAccounted(pids, 3, 74) returns
    //
    // false

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
}

void getOffending(process **processes, size_t count, long int threshhold)
{
    // This function will take in the array "process **processes" along with its length "size_t count" as well as a threshhold "long int threshhold"
    // and will print all the offending process in the format PID (FD), where FD represents the total number of fds for that process.
    // NOTES: We define an offending process as a process that has a number of file descriptors that exceeds the given threshhold.
    // Example Output:
    /// size_t count = 15 and fill the array process **processes with the 15 process structs like so:
    // process **processes = {{ 118743, 0, "/dev/null", 5}, ........., {118743, 25, "socket:[642073]", 642073}} where ... represents the other 13 process structs
    // getOffending(processes, count, 10) will print
    //
    // ## Offending processes:
    // 118743 (15),

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

    // FOR EXAMPLE OUTPUT REFER TO THE EXAMPLE OUTPUT OF getCompositeTable(). But in this case this will be printed in the compositeTable.txt file in the current directory

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

    // FOR EXAMPLE OUTPUT REFER TO THE EXAMPLE OUTPUT OF getCompositeTable(). But in this case this will be printed in binary in the compositeTable.bin file in the current directory

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
    // NOTE: THAT IF NEITHER (--composite, --per-process, --systemWide, --Vnodes) than we will print all these tables. Additionally we assume that threshold operates
    // independantly from the pid positional flag (this means that threshold will search all processes even if a particular process is inputted as a CLA).
    // Example Output:
    // ./fdTables 1234 --composite
    // parseArguments(int argc, char *argv[], bool *composite, bool *per_process, bool *system, bool *vnodes, int *threshold, long int *pid) will set:
    //
    // compsite = true, pid = 1234, the rest of booleans to false, and the rest of int to -1
    // Example Output 2:
    // ./fdTables --Vnodes --threshold=12 45362
    // parseArguments(int argc, char *argv[], bool *composite, bool *per_process, bool *system, bool *vnodes, int *threshold, long int *pid) will set:
    //
    // vnodes = true, pid = 1234, threshold = 12, and the rest of booleans to false

    // if there is CLA
    if (argc > 1)
    {
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
            if (sscanf(argv[i], "--threshold=%d", &temp) == 1 && temp >= 0)
            {
                *threshold = temp;
            }
            // check for PID positional argument
            long int temp_pid;
            if (sscanf(argv[i], "%ld", &temp_pid) == 1)
            {
                *pid = temp_pid;
            }
        }
    }
    // no CLA
    else if (argc == 1)
    {
        *composite = true;
        *per_process = true;
        *system = true;
        *vnodes = true;
    }
    // if no CLA except pid or threshold
    if (((*pid != -1) || (*threshold != -1)) && *composite == false && *per_process == false && *system == false && *vnodes == false)
    {
        *composite = true;
        *per_process = true;
        *system = true;
        *vnodes = true;
    }
}

bool validateArguments(int argc, char *argv[])
{
    // This functions takes int argc and char *argv[] and validates the command line arguments inputted by returning true if they are correct and
    // false if they are not. The validation includes checking for repeated arguments, mistyped arguments, too many argumenys, and correct use of positional arguments.
    // Example Output:
    // ./fdTables --composite 1234 returns
    //
    // true
    // Example Output 2:
    // ./fdTables --composite 1234 --composite returns
    //
    // false
    // and prints "REPEATED ARGUMENTS. TRY AGAIN!

    // keep track of how many times each arg is called
    int compositeArgCount = 0;
    int perProcessArgCount = 0;
    int systemArgCount = 0;
    int vnodesArgCount = 0;
    int thresholdArgCount = 0;
    int positionalArgCount = 0;

    // check number of arguments
    if (argc > 7)
    {
        printf("TOO MANY ARGUMENTS. TRY AGAIN!\n");
        return false;
    }

    // iterate argv to check for correctness
    for (int i = 1; i < argc; i++)
    {
        long int dummyValue;
        int secondDummyValue;

        // check if all the flags are correctly formated
        if (argc > 1)
        {
            if (strcmp(argv[i], "--per-process") != 0 && strcmp(argv[i], "--systemWide") != 0 && strcmp(argv[i], "--Vnodes") != 0 && strcmp(argv[i], "--composite") != 0 && sscanf(argv[i], "%ld", &dummyValue) != 1 && sscanf(argv[i], "--threshold=%d", &secondDummyValue) != 1)
            {
                printf("ONE OR MORE ARGUMENTS ARE MISTYPED. TRY AGAIN!\n");
                return false;
            }
        }

        // check if there are repeated arguments
        if (strcmp(argv[i], "--per-process") == 0)
        {
            perProcessArgCount++;
            if (perProcessArgCount > 1)
            {
                printf("REPEATED ARGUMENTS. TRY AGAIN!\n");
                return false;
            }
        }
        else if (strcmp(argv[i], "--systemWide") == 0)
        {
            systemArgCount++;
            if (systemArgCount > 1)
            {
                printf("REPEATED ARGUMENTS. TRY AGAIN!\n");
                return false;
            }
        }
        else if (strcmp(argv[i], "--Vnodes") == 0)
        {
            vnodesArgCount++;
            if (vnodesArgCount > 1)
            {
                printf("REPEATED ARGUMENTS. TRY AGAIN!\n");
                return false;
            }
        }
        else if (strcmp(argv[i], "--composite") == 0)
        {
            compositeArgCount++;
            if (compositeArgCount > 1)
            {
                printf("REPEATED ARGUMENTS. TRY AGAIN!\n");
                return false;
            }
        }
        else if (sscanf(argv[i], "--threshold=%d", &secondDummyValue) == 1)
        {
            thresholdArgCount++;
            if (thresholdArgCount > 1)
            {
                printf("REPEATED ARGUMENTS. TRY AGAIN!\n");
                return false;
            }
        }
        else if (sscanf(argv[i], "%ld", &dummyValue) == 1)
        {
            positionalArgCount++;
            if (positionalArgCount > 1)
            {
                printf("REPEATED ARGUMENTS. TRY AGAIN!\n");
                return false;
            }
        }
    }

    return true;
}

void navigate(int argc, char *argv[])
{
    // This function will take in int argc, char *argv[] and will validate/parse the inputted arguments as well as help navigate to the right output
    // depening on the command line arguments given.
    // Example Output:
    // ./fdTables --composite 3391894
    // navigate(argc, argv[]) will print
    //
    //  PID       FD        Filename                      	Inode
    //  ======================================================================
    //  3391894   0         /dev/null                     	6
    //  3391894   1         socket:[1748824698]           	1748824698
    //  3391894   2         socket:[1748824698]           	1748824698
    //  3391894   3         socket:[1748838307]           	1748838307
    //  3391894   4         anon_inode:[eventpoll]        	10286
    //  3391894   5         anon_inode:[signalfd]         	10286
    //  3391894   6         anon_inode:inotify            	10286
    //  3391894   7         /sys/fs/cgroup/unified/user.slice/user-23629403.slice/user@23629403.service	256456
    //  3391894   8         anon_inode:[timerfd]          	10286
    //  3391894   9         anon_inode:[eventpoll]        	10286
    //  3391894   10        /proc/3391894/mountinfo       	1748838314
    //  3391894   11        anon_inode:inotify            	10286
    //  3391894   12        socket:[1748838341]           	1748838341
    //  3391894   13        anon_inode:inotify            	10286
    //  3391894   14        /proc/swaps                   	4026532071
    //  3391894   15        socket:[1748838315]           	1748838315
    //  3391894   16        socket:[1748838328]           	1748838328
    //  3391894   17        socket:[1748838329]           	1748838329
    //  3391894   18        socket:[1748838330]           	1748838330
    //  3391894   19        socket:[1748838331]           	1748838331
    //  3391894   20        socket:[1748838333]           	1748838333
    //  3391894   21        anon_inode:[timerfd]          	10286
    //  3391894   26        socket:[1748838346]           	1748838346
    //  3391894   27        socket:[1748838348]           	1748838348
    //  3391894   28        socket:[1748838350]           	1748838350
    //  3391894   29        socket:[1748838352]           	1748838352
    //  3391894   30        socket:[1748838354]           	1748838354
    //  3391894   31        socket:[1748838356]           	1748838356
    //  ======================================================================

    if (validateArguments(argc, argv) == true)
    {

        // interpret the called arguments
        bool composite = false;
        bool per_process = false;
        bool system = false;
        bool vnodes = false;
        int threshold = -1;
        long int pid = -1;

        // get all processes
        process **processes = (process **)malloc(sizeof(process *));
        size_t count = getProcesses(processes);

        parseArguments(argc, argv, &composite, &per_process, &system, &vnodes, &threshold, &pid);

        // call the needed functions
        if (pidExists(processes, count, pid) == true)
        {
            if (per_process)
            {
                getPerProcess(processes, count, pid);
            }
            if (system)
            {
                getSystemWide(processes, count, pid);
            }
            if (vnodes)
            {
                getVnodes(processes, count, pid);
            }
            if (composite)
            {
                getCompositeTable(processes, count, pid);
            }
            if (threshold != -1)
            {
                getOffending(processes, count, threshold);
            }
        }
        else
        {
            printf("THE SELECTED PID DOES NOT EXIST\n\n");
        }
    }
}

int main(int argc, char *argv[])
{
    // call the navigate function which will redirect to the right output depeneding on the arguments
    navigate(argc, argv);
}
