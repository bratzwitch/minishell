#include "../include/minishell.h"

void	piping(t_token **tokens, int pipe_count, char *env)
{

	pid_t pid;
	int i = 0;
	t_token *temp = *tokens;
	int prev_pipe = -1;

	int pipes[pipe_count][2];
	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipes[i]) < 0)
		{
			perror("pipe");
			return ;
		}
		i++;
	}

	while (temp && temp->type != TOKEN_EOF)
	{
		if (temp->type == TOKEN_PIPE)
		{
			temp = temp->next;
			continue ;
		}
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

			char *args[] = {temp->value, NULL};
			execve(args[0], args, &env);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			prev_pipe = i;
			temp = temp->next;
			i++;
		}
	}
	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i <= pipe_count)
	{
		wait(NULL);
		i++;
	}
}