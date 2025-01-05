#include "../include/minishell.h"

void wait_for_children(int pipe_count)
{
	int i;

	i = 0;
	while (i <= pipe_count)
	{
		wait(NULL);
		i++;
	}
}

void close_all_pipes(int pipes[][2], int pipe_count)
{
	int i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void execute_command(t_token *temp, int pipes[][2], int prev_pipe, int i, int pipe_count, char *env)
{
	char *args[] = {temp->value, NULL};

	if (prev_pipe != -1)
	{
		close(pipes[prev_pipe][1]);
		dup2(pipes[prev_pipe][0], STDIN_FILENO);
		close(pipes[prev_pipe][0]);
	}
	if (i < pipe_count)
	{
		close(pipes[i][0]);
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
	execve(args[0], args, &env);
	perror("execve");
	exit(EXIT_FAILURE);
}

bool create_pipes(int pipes[][2], int pipe_count)
{
	int i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipes[i]) < 0)
		{
			perror("pipe");
			return (false);
		}
		i++;
	}
	return (true);
}
/* This function handles a pipeline of commands connected via pipes.
	Each command runs in a child process, and the pipes manage data flow between them. */
void piping(t_token *tokens, int pipe_count, char *env)
{
	int pipes[pipe_count][2]; // it is not allowed - VLA
	int prev_pipe = -1; // Keeps track of the previous pipe's index for connecting the pipeline.
	t_token *temp = tokens;
	int i;
	pid_t pid;

	if (!create_pipes(pipes, pipe_count))
		return;
	i = 0;
	while (temp && temp->type != TOKEN_EOF)
	{
		if (temp->type == TOKEN_PIPE)
			temp = temp->next;
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return;
		}
		if (pid == 0)
			execute_command(temp, pipes, prev_pipe, i, pipe_count, env);
		prev_pipe = i;
		temp = temp->next;
		i++;
	}
	close_all_pipes(pipes, pipe_count);
	wait_for_children(pipe_count);
}

/* 	int pipes[pipe_count][2]; - not allowed (VLA - variable-length arrays); see 42 norm */

// int pipes[pipe_count][2];
/* Creates a 2D array of pipes where each pipes[i] has two file descriptors:
		pipes[i][0]: Read end of the pipe.
		pipes[i][1]: Write end of the pipe.
	However, you cannot use variable-length arrays.
		You’ll need to dynamically allocate memory instead. */

/* pipe() creates a pair of file descriptors, one for reading and one for writing. 
		pipefd[0] refers to the read end of the pipe.
		pipefd[1] refers to the write end of the pipe.
	On  success,  zero  is  returned.   On  error, -1 is returned, 
			errno is set appropriately, and pipefd is left unchanged. */