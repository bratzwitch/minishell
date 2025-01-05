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
		{
			pipes += 1;
			printf("pipe counted %d\n", pipes);
		}
		temp = temp->next; // we had "temp++;" and it does not iterate the list
	}
	return (pipes);
}
