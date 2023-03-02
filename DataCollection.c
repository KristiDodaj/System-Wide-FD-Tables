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
} process_info;

// This function will populate a dynamic array with the process data strcutures defined above.

void getProcesses(process_info **processes_ptr, size_t *num_processes_ptr)
{

    // Open directory /proc
    DIR *dir = opendir("/proc");
    if (dir == NULL)
    {
        perror("opendir failed");
        exit(1);
    }

    // Iterate over directory entries
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // Check if entry is a directory and its name consists of digits
        if (entry->d_type == DT_DIR && atoi(entry->d_name) != 0)
        {
            // Open file /proc/<pid>/fd
            char fd_path[256];
            sprintf(fd_path, "/proc/%s/fd", entry->d_name);
            int fd_dir = open(fd_path, O_RDONLY);
            if (fd_dir == -1)
            {
                continue; // Skip process if can't open fd directory
            }

            // Iterate over file descriptor entries
            struct dirent *fd_entry;
            while ((fd_entry = readdir(fd_dir)) != NULL)
            {
                // Get inode of file descriptor
                char fd_file_path[256];
                sprintf(fd_file_path, "/proc/%s/fd/%s", entry->d_name, fd_entry->d_name);
                struct stat stat_buf;
                if (stat(fd_file_path, &stat_buf) == -1)
                {
                    continue; // Skip file descriptor if can't stat it
                }
                if (!S_ISREG(stat_buf.st_mode))
                {
                    continue; // Skip file descriptor if it's not a regular file
                }

                // Create new process_info struct and append to dynamic array
                process_info new_process = {
                    .pid = strdup(entry->d_name),
                    .fd = strdup(fd_entry->d_name),
                    .filename = NULL,
                    .inode = stat_buf.st_ino};
                *processes_ptr = realloc(*processes_ptr, sizeof(process_info) * (*num_processes_ptr + 1));
                if (*processes_ptr == NULL)
                {
                    perror("realloc failed");
                    exit(1);
                }
                (*processes_ptr)[(*num_processes_ptr)++] = new_process;
            }

            close(fd_dir);
        }
    }

    // Iterate over dynamic array and get filenames
    for (size_t i = 0; i < *num_processes_ptr; i++)
    {
        char link_path[256];
        sprintf(link_path, "/proc/%s/fd/%s", (*processes_ptr)[i].pid, (*processes_ptr)[i].fd);
        char target_path[256];
        ssize_t target_len = readlink(link_path, target_path, sizeof(target_path) - 1);
        if (target_len != -1)
        {
            target_path[target_len] = '\0';
            (*processes_ptr)[i].filename = strdup(target_path);
        }
    }

    closedir(dir);
}

int main()
{
    // Allocate an initial array with capacity for 10 elements
    size_t max_processes = 10;
    process_info *processes = malloc(sizeof(process_info) * max_processes);
    if (processes == NULL)
    {
        perror("malloc failed");
        exit(1);
    }

    // Call function to populate array
    size_t num_processes = 0;
    get_user_processes(&processes, &num_processes);

    // Print information about processes
    for (size_t i = 0; i < num_processes; i++)
    {
        printf("PID: %s, FD: %s, Filename: %s, Inode: %ld\n",
               processes[i].pid, processes[i].fd, processes[i].filename, processes[i].inode);
    }

    // Free memory
    for (size_t i = 0; i < num_processes; i++)
    {
        free(processes[i].pid);
        free(processes[i].fd);
        free(processes[i].filename);
    }
    free(processes);

    return 0;
}