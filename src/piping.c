#include "../include/minishell.h"

void split_tokens_by_pipe(t_token *head, t_token **list1, t_token **list2)
{
	t_token *current = head;
	t_token *prev = NULL;

	*list1 = head;
	*list2 = NULL;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			*list2 = current->next;
			if (prev)
				prev->next = NULL;
			current->next = NULL;
			return;
		}
		prev = current;
		current = current->next;
	}
}

int pipe_execute(t_token *tokens, char **env)
{
	char **args;
	char *path;

	path = find_command(tokens->value, getenv("PATH"));
	if (!path)
	{
		free(path);
		printf("no such command sucker\n");
		return (127);
	}
	args = lst_to_arr(tokens);
	// printf("executed %s\n", path);
	if (execve(path, args, env) < 0)
	{
		printf("no execve today\n");
		return (-1);
	}
	return (0);
}

void execute_pipe_segment(t_token *segment, int input_fd, int output_fd, char **env)
{
	if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	(void)output_fd;
	// if (output_fd != -1)
	// {
	// 	dup2(output_fd, STDOUT_FILENO);
	// 	close(output_fd);
	// }
	pipe_execute(segment, env);
	exit(1);
}

void close_unused_pipe(int pipe_fd)
{
	if (pipe_fd != -1)
		close(pipe_fd);
}

void wait_for_children(int child_count)
{
	int i = 0;

	while (i < child_count)
	{
		wait(NULL);
		i++;
	}
}

void create_pipes(int i, int pipe_count, int fd[2])
{
	if (i < pipe_count && pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

pid_t create_fork()
{
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	printf("forked pid: %d\n", pid);
	return (pid);
}

void handle_child_process_pipe(int prev_pipe, int i, int pipe_count, int fd[2], t_token *list1, char **env)
{
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	(void)i;
	(void)pipe_count;
	// if (i < pipe_count)
	// {
	// 	close(fd[0]);
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[1]);
	// }
	// else
	// {
	// 	close(fd[1]);
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[0]);
	// }
	execute_pipe_segment(list1, prev_pipe, fd[1], env);
	exit(1);
}

void handle_parent_process_pipe(int fd[2], int *prev_pipe)
{
	close(fd[1]);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	*prev_pipe = fd[0];
}
void init_piping_vars(t_prompt *prompt, int *prev_pipe, t_token **current_tokens, int *pipe_count)
{
	*prev_pipe = -1;
	*current_tokens = prompt->token_lst;
	*pipe_count = count_pipes(*current_tokens);
}

void piping(t_prompt *prompt, char **env)
{
	int prev_pipe;
	int fd[2];
	int pipe_count;
	int i = 0;
	t_token *current_tokens;
	t_token *list1;
	t_token *list2;
	pid_t pid;

	init_piping_vars(prompt, &prev_pipe, &current_tokens, &pipe_count);
	while (i <= pipe_count)
	{
		list1 = NULL;
		list2 = NULL;
		split_tokens_by_pipe(current_tokens, &list1, &list2);
		current_tokens = list2;
		create_pipes(i, pipe_count, fd);
		pid = create_fork();
		if (pid == 0)
			handle_child_process_pipe(prev_pipe, i, pipe_count, fd, list1, env);
		else
			handle_parent_process_pipe(fd, &prev_pipe);
		i++;
	}
	close_unused_pipe(prev_pipe);
	wait_for_children(pipe_count + 1);
}

/* This function handles a pipeline of commands connected via pipes.
	Each command runs in a child process,
		and the pipes manage data flow between them. */

// Surprise 💀, ✨compiling error✨, pls take a look on piping.c
// Eva plssss i need help with tokens, i dont understand wtf is goind on
// and what i can do to stop "ls" for example work with futh	// printf("executed %s\n", path);er arguments
// here is example with multiple pipes, as you see all executing but ls still trying to work with all arguments
// minishell$>ls | pwd | ls
// pipe counted 1
// pipe counted 2
// Executing command: ls
// ls: cannot access '|': No such file or directory
// ls: cannot access 'pwd': No such file or directory
// ls: cannot access '|': No such file or directory
// ls: cannot access 'ls': No such file or directory
// Executing command: pwd
// pwd: ignoring non-option arguments
// /sgoinfre/vmoroz/evalminishell
// Executing command: ls
// breakpoints.gdb  libft     minishell       README.md
// include          Makefile  minishell.supp  src
// ls: cannot access '|': No such file or directory
// ls: cannot access 'pwd': No such file or directory
// ls: cannot access '|': No such file or directory
// ls: cannot access 'ls': No such file or directory
// Process exited with status 2

/* 	int pipes[pipe_count][2]; - not allowed (VLA
		- variable-length arrays); see 42 norm */

// int pipes[pipe_count][2];
/* Creates a 2D array of pipes where each pipes[i] has two file descriptors:
		pipes[i][0]: Read end of the pipe.
		pipes[i][1]: Write end of the pipe.
	However, you cannot use variable-length arrays.
		You’ll need to dynamically allocate memory instead. */

/* pipe() creates a pair of file descriptors,
	one for reading and one for writing.
		pipefd[0] refers to the read end of the pipe.
		pipefd[1] refers to the write end of the pipe.
	On  success,  zero  is  returned.   On  error, -1 is returned,
			errno is set appropriately, and pipefd is left unchanged. */