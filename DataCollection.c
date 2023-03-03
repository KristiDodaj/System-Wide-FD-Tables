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

    // Get the UID of the current user
    uid_t user_id = getuid();

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

            // Check if the current process is owned by the current user
            char uid_path[256];
            snprintf(uid_path, 256, "/proc/%ld/status", pid);
            FILE *status = fopen(uid_path, "r");
            if (status == NULL)
            {
                continue;
            }
            char line[256];
            while (fgets(line, 256, status))
            {
                if (strncmp(line, "Uid:", 4) == 0)
                {
                    uid_t proc_uid = atoi(line + 5);
                    if (proc_uid == user_id)
                    {
                        // enter the fd directory given pid
                        char path[4096];
                        snprintf(path, 4096, "/proc/%s/fd", entry->d_name);
                        DIR *fd_directory = opendir(path);

                        // when unsucesfully opened
                        if (fd_directory == NULL)
                        {
                            continue;
                        }

                        // go through fd files
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
                            snprintf(path, 4096, "/proc/%ld/fd/%s", pid, fd_entry->d_name);

                            char filename[4096];
                            ssize_t len = readlink(path, filename, 4096);
                            if (len == -1)
                            {
                                perror("readlink");
                                continue;
                            }
                            filename[len] = '\0';

                            printf("PID: %ld\tFD: %d\tFilename: %s\n", pid, fd, filename);
                        }
                        closedir(fd_directory);
                    }
                }
            }
            fclose(status);
        }
    }
    closedir(directory);
}

int main()
{
    getProcesses();
}