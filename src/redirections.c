#include "../include/minishell.h"

int	input_redirection(const char *file_name)
// < ; pass token->value as a parameter
{
	int fd_in;

	fd_in = open(file_name, O_RDONLY);
	if (fd_in == -1)
	{
		perror("Error opening file.");
		return (-1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	// any future reads from stdin will now read from fd
	{
		perror("Error redirecting input.");
		close(fd_in);
		return (-1);
	}
	close(fd_in);
	return (0);
}

int	output_redirection(const char *file_name)
{
	int	fd_out;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	// if (type == TOKEN_REDIRECT_APPEND)
	// 	flags |= O_APPEND;
	// else
	// 	flags |= O_TRUNC;
	fd_out = open(file_name, flags, 0644);
	if (fd_out == -1)
	{
		perror("Error opening file for output redirection");
		return (-1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output");
		close(fd_out);
		return (-1);
	}
	close(fd_out);
	return (0);
}

// printf("This goes to the file\n");
// dup2(stdout_copy, STDOUT_FILENO);
// close(stdout_copy); // not closing file descriptors can lead to memory leaks
/*
O_WRONLY: This flag specifies that the file is opened for write-only access.
O_CREAT: This flag tells the system to create the file if it does not exist.
O_TRUNC: This flag clears its contents if it already exists.
0644: rw-r--r-- (Owner can read/write, group and others can read)

dup vs dup2
- dup duplicates an existing file descriptor to the lowest available file descriptor. E.g. int new_fd = dup(fd);
- dup2 allows you to specify exactly which file descriptor to duplicate to. E.g. dup2(fd,
	STDIN_FILENO);
stdin (standard input) is a predefined file descriptor (0) that a program uses to read input.
*/
