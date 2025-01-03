#include "../include/minishell.h"

void	piping(t_token **tokens,int pipes,char *args[], char *env)
{
	int fd[2];
	pid_t first;
	pid_t second;
    (void)pipes;
    (void)args;
    (void)env;

	if (pipe(fd) < 0)
	{
		printf("no\n");
		return ;
	}
	first = fork();
	if (first < 0)
	{
		printf("sill no\n");
		return ;
	}
	if (first == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (!tokens)
		{
			printf("cool");
			exit(0);
		}
	}
	else
	{
		second = fork();
		if (second < 0)
		{
			printf("sill no\n");
			return ;
		}
		if (second == 0)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			if (!tokens)
            {
                printf("cool");
                exit(0);
            }
				
		}
		else
		{
			wait(NULL);
			wait(NULL);
		}
	}
}