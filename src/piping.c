#include "../include/minishell.h"

void	wait_for_children(int pipe_count)
{
	int	i;

	i = 0;
	while (i <= pipe_count)
	{
		wait(NULL);
		i++;
	}
}

// void close_all_pipes(int pipes[][2], int pipe_count)
// {
// 	int i;

// 	i = 0;
// 	while (i < pipe_count)
// 	{
// 		close(pipes[i][0]);
// 		close(pipes[i][1]);
// 		i++;
// 	}
// }

// void execute_command(t_token *temp, int pipes[][2], int prev_pipe, int i,
//	int pipe_count, char *env)
// {
// 	char *args[] = {temp->value, NULL};

// 	if (prev_pipe != -1)
// 	{
// 		close(pipes[prev_pipe][1]);
// 		dup2(pipes[prev_pipe][0], STDIN_FILENO);
// 		close(pipes[prev_pipe][0]);
// 	}
// 	if (i < pipe_count)
// 	{
// 		close(pipes[i][0]);
// 		dup2(pipes[i][1], STDOUT_FILENO);
// 		close(pipes[i][1]);
// 	}
// 	execve(args[0], args, &env);
// 	perror("execve");
// 	exit(EXIT_FAILURE);
// }

// bool create_pipes(int pipes[][2], int pipe_count)
// {
// 	int i;

// 	i = 0;
// 	while (i < pipe_count)
// 	{
// 		if (pipe(pipes[i]) < 0)
// 		{
// 			perror("pipe");
// 			return (false);
// 		}
// 		i++;
// 	}
// 	return (true);
// }
/* This function handles a pipeline of commands connected via pipes.
	Each command runs in a child process,
		and the pipes manage data flow between them. */

void	piping(t_prompt *prompt, int pipe_count, char **env)
{
	int			fd[2];
	int			prev_pipe;
	t_token		*temp;
	int			i;
	pid_t		pid;
	t_prompt	tmp;

	(void)pipe_count;
	(void)env;
	prev_pipe = -1;
	temp = prompt->token_lst;
	// if (!create_pipes(pipes, pipe_count))
	// 	return ;
	i = 0;
	while (temp && temp->type != TOKEN_EOF)
	{
		pipe(fd);
		while (temp && temp->type == TOKEN_PIPE)
			temp = temp->next;
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
		{
			if (prev_pipe != -1)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (temp->next && temp->next->type != TOKEN_PIPE)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
			}
			// else
			// {
			// 	close(fd[1]);
			// }
			tmp.token_lst = temp;
			tmp.path = find_command(temp->value, getenv("PATH"));
			if (tmp.path)
			{
				printf("Executing command: %s\n", temp->value);
				execute(&tmp, env);
				// if (execve(tmp.path, lst_to_arr(temp), env) < 0)
                //     printf("no");
			}
			else
				printf("no");
			close(fd[0]);
			close(fd[1]);
			exit(0);
		}
		else
		{
			close(fd[1]);
			if (prev_pipe != -1)
			{
				close(prev_pipe);
			}
			prev_pipe = fd[0];
			temp = temp->next;
		}
		i++;
		// need to implement remembering of output frfr
		// handling multiple pipes also needed frfr
	}
	wait_for_children(i);
	if (prev_pipe != -1)
		close(prev_pipe);
	// close_all_pipes(pipes, pipe_count);
}

// Surprise 💀, ✨compiling error✨, pls take a look on piping.c
// Eva plssss i need help with tokens, i dont understand wtf is goind on
// and what i can do to stop "ls" for example work with futher arguments
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