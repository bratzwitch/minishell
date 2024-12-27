#include "../../include/minishell.h"

void lexer(char *input)
{
	t_token *t;
	int exit_status;

	t = NULL;
	exit_status = 0;
	while ((t = get_next_token(&input, &exit_status)) != NULL && t->type != TOKEN_EOF)
	{
		if (t->type == TOKEN_ERROR || !t)
			break ;
		printf("Token Type: %d, Token Value: %s\n", t->type, t->value);
		free_token(t);
	}
	if (t)
		free_token(t);
}
