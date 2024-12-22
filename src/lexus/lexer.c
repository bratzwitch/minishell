#include "../../include/minishell.h"

void lexer(char *input)
{
	t_token *t;
	int exit_status;

	t = NULL;
	exit_status = 0;
	t = get_next_token(&input, &exit_status);
	while (t->type != TOKEN_EOF)
	{
		if (t->type == TOKEN_ERROR)
		{
			printf("Nope bye\n");
			free(t);
			break;
		}
		printf("Token Type: %d, Token Value: %s\n", t->type, t->value);
		free_token(t);
		t = get_next_token(&input, &exit_status);
	}
	free_token(t);
}
