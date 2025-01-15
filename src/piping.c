#include "../include/minishell.h"

void	handle_child_process_pipe(t_pipe *pipe, char **env)
{
	if (ft_is_special_token(pipe->list2) == TOKEN_HEREDOC)
	{
		if (heredoc_redirection(pipe->list2->next->value) == -1)
		{
			printf("Heredoc redirection failed.\n");
			return ;
		}
	}
	if (pipe->prev_pipe != -1) // If there's a previous pipe, redirect input
	{
		if (dup2(pipe->prev_pipe, STDIN_FILENO) == 1)
			perror("dup2 fd[1]");
		close(pipe->prev_pipe);
	}
	if (pipe->i < pipe->pipe_count) // Redirect output if not the last command
	{
		if (dup2(pipe->fd[1], STDOUT_FILENO) == -1)
			perror("dup2 fd[1]");
		close(pipe->fd[1]);
	}
	else
	{
		close(pipe->fd[1]);
	}
	close(pipe->fd[0]);
	execute(pipe->list1, NULL, env);
	exit(1);
}

void handle_parent_process_pipe(int fd[2], int *prev_pipe)
{
	close(fd[1]);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	*prev_pipe = fd[0];
}

void	piping(t_prompt *prompt, char **env)
{
	t_pipe	pipe;

	pipe.current_tokens = prompt->token_lst;
	pipe.list1 = NULL;
	pipe.list2 = NULL;
	pipe.pipe_count = count_pipes(prompt->token_lst);
	pipe.prev_pipe = -1;
	pipe.i = 0;
	while (pipe.i <= pipe.pipe_count)
	{
		split_tokens(pipe.current_tokens, &pipe.list1, &pipe.list2, TOKEN_PIPE);
		pipe.current_tokens = pipe.list2;
		// if (ft_is_special_token(pipe.list1) == TOKEN_HEREDOC)
		// {
		//     if (heredoc_redirection(pipe.list1->next->value,heredoc_pipe) == -1)
		//     {
		//         printf("Heredoc redirection failed.\n");
		//         return ;
		//     }
		// }
		create_pipes(pipe.i, pipe.pipe_count, pipe.fd);
		pipe.pid = create_child_process();
		if (pipe.pid == 0)
			handle_child_process_pipe(&pipe, env);
		else
			handle_parent_process_pipe(pipe.fd, &pipe.prev_pipe);
		pipe.i++;
	}
	if (pipe.prev_pipe != -1)
		close(pipe.prev_pipe);
	wait_for_children(pipe.pipe_count + 1);
}

/* SLAVA. tested some of the commands bellow - YEVA 8.1.25
			ls -l | wc -l
			ls -la | grep something | wc -l
			cat test | grep something
			env | grep PWD
	WHEN YOU USE GREP DO NOT USE THE QUOTES ("") AND FOR NOW IT CAN ONLY TAKE ONE WORD I THINK
*/

/* This function handles a pipeline of commands connected via pipes.
	Each command runs in a child process,
		and the pipes manage data flow between them. */

// Surprise 💀, ✨compiling error✨, pls take a look on piping.c
// Eva plssss i need help with tokens, i dont understand wtf is goind on
// and what i can do to stop "ls" for example work with futh	// printf("executed
//	%s\n", path);er arguments
// here is example with multiple pipes,
// as you see all executing but ls still trying to work with all arguments
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