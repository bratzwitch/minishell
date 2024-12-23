#include "../../include/minishell.h"

bool ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

void free_token(t_token *t)
{
    if (!t)
        return;
    if (t->type == TOKEN_ARGUMENT)
        free(t->value);
    free(t);
}
