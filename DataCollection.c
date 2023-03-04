#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

// This CDT represents a single process including it's information (pid, fd, filename, inode)

typedef struct
{
    long int pid;
    long int fd;
    char *filename;
    long int inode;
} process;

// This function will populate a dynamic array with the process data strcutures defined above and returns the number of processes found.

int getProcesses(process *processes)
{

    // open the /proc directory
    DIR *directory = opendir("/proc");

    // get the UID of the current user
    uid_t user_id = getuid();

    // count the number of processes
    int count = 0;

    // check if sucessfully opened
    if (directory == NULL)
    {
        perror("Opening /proc directory failed");
    }

    // go through the directory entries
    struct dirent *entry;
    while ((entry = readdir(directory)) != NULL)
    {
        long int pid;
        char *endPointer;

        // validate that the entry is a directory that is a PID
        if (entry->d_type == DT_DIR && (pid = strtol(entry->d_name, &endPointer, 10)) >= 0 && *endPointer == '\0')
        {

            // open status file for each pid to check if it is a user owned process
            char uid_path[256];
            snprintf(uid_path, 256, "/proc/%ld/status", pid);
            FILE *status = fopen(uid_path, "r");
            if (status == NULL)
            {
                continue;
            }

            // find uid section in file
            char line[256];
            while (fgets(line, 256, status))
            {

                // check is it is a user owned process
                if (strncmp(line, "Uid:", 4) == 0)
                {
                    uid_t process_uid = atoi(line + 5);
                    if (process_uid == user_id)
                    {
                        // enter the fd directory given pid
                        char fd_path[4096];
                        snprintf(fd_path, 4096, "/proc/%s/fd", entry->d_name);
                        DIR *fd_directory = opendir(fd_path);

                        // when unsucesfully opened
                        if (fd_directory == NULL)
                        {
                            continue;
                        }

                        // go through fd directories
                        struct dirent *fd_entry;
                        while ((fd_entry = readdir(fd_directory)) != NULL)
                        {
                            // skip over "." and ".."
                            if (strcmp(fd_entry->d_name, ".") == 0 || strcmp(fd_entry->d_name, "..") == 0)
                            {
                                continue;
                            }

                            // update the fd file path
                            int fd = atoi(fd_entry->d_name);
                            char fd_file_path[4096];
                            snprintf(fd_file_path, 4096, "/proc/%ld/fd/%s", pid, fd_entry->d_name);

                            // get filename
                            char filename[4096];
                            ssize_t len = readlink(fd_file_path, filename, 4096);

                            // if readlink did not work
                            if (len == -1)
                            {
                                perror("readlink");
                                continue;
                            }
                            filename[len] = '\0';

                            // create stat structs to get inode number
                            struct stat fd_stat;
                            if (stat(fd_file_path, &fd_stat) == -1)
                            {
                                continue;
                            }

                            if (count > 1)
                            {
                                processes = realloc(processes, (count + 1) * sizeof(process));
                            }
                            processes[count].pid = pid;
                            processes[count].fd = fd;
                            strcpy(processes[count].filename, filename);
                            processes[count].inode = fd_stat.st_ino;

                            // update count
                            count++;

                            printf("PID: %ld\tFD: %d\tFilename: %s Inode: %ld\n", pid, fd, filename, fd_stat.st_ino);
                        }

                        // close the opened files and directories
                        closedir(fd_directory);
                    }
                }
            }
            fclose(status);
        }
    }
    closedir(directory);

    return count;
}

int main()
{
    process *processes;
    int count = getProcesses(processes);

    printf("================================\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-10ld %-10ld %-50s %lu\n", processes[i].pid, processes[i].fd, processes[i].filename, processes[i].inode);
    }
}
