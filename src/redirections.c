#include "../include/minishell.h"

int input_redirection(const char *file_name) // < ; pass token->value as a parameter
{
    int fd;

    fd = open(file_name, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file.");
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1) // any future reads from stdin will now read from fd
    {
        perror("Error redirecting input.");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}

int output_redirection(const char *file_name) // > redirects stdout to a file.
{
    int fd;
    int stdout_copy;
    
    stdout_copy = dup(STDOUT_FILENO);
    fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    /*
    O_WRONLY: This flag specifies that the file is opened for write-only access.
    O_CREAT: This flag tells the system to create the file if it does not exist.
    O_TRUNC: This flag clears its contents if it already exists.
    0644: rw-r--r-- (Owner can read/write, group and others can read)
    */
    if (fd == -1)
    {
        perror("Error opening file");
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("Error redirecting stdout");
        close(fd);
        return (-1);
    }
    close(fd);
    printf("This goes to the file\n");
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdout_copy); // not closing file descriptors can lead to memory leaks
    return (0);
}

/*
dup vs dup2
    - dup duplicates an existing file descriptor to the lowest available file descriptor. E.g. int new_fd = dup(fd);
    - dup2 allows you to specify exactly which file descriptor to duplicate to. E.g. dup2(fd, STDIN_FILENO);
stdin (standard input) is a predefined file descriptor (0) that a program uses to read input.
*/
