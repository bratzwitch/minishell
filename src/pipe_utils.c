#include "../include/minishell.h"

int count_pipes(t_token *token_lst)
{
	t_token *temp;
	int pipes;

	pipes = 0;
	temp = token_lst;
	while (temp != NULL)
	{
		if (temp->type == TOKEN_PIPE)
			pipes += 1;
		temp = temp->next;
	}
	return (pipes);
}

void create_pipes(int i, int pipe_count, int fd[2])
{
	if (i < pipe_count && pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void wait_for_children(int child_count)
{
	int i = 0;
	int exit_status;

	while (i < child_count)
	{
		if (wait(&exit_status) > 0)
		{
			if (WIFEXITED(exit_status))
				received_sig = WEXITSTATUS(exit_status);
			else if (WIFSIGNALED(exit_status))
				received_sig = 128 + WTERMSIG(exit_status);
			else if (WIFSTOPPED(exit_status))
				received_sig = WSTOPSIG(exit_status);
		}
		else
			printf("child did not exit normally.\n");
		i++;
	}
}
