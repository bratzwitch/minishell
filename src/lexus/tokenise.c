#include "../../include/minishell.h"
#include <string.h>

t_token *create_token(t_token_type type, char *value)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		perror("Failed to allocate a token.");
		return (NULL);
	}
	new_token->type = type;
	if (value)
	{
		new_token->value = value;
	}
	else
	{
		// new_token->type = TOKEN_ERROR;
		new_token->value = NULL;
	}
	return (new_token);
}

t_token *handle_argument(char **input)
{
	char *current = *input;
	char *start = current;

	while (*current && !ft_isspace(*current) && *current != '<' && *current != '>' && *current != '|' && *current != '$')
		current++;

	*input = current;
	char *token_value = strndup(start, current - start);
	if (!token_value)
	{
		perror("Memory allocation failed for token_value");
		return NULL;
	}
	return (create_token(TOKEN_ARGUMENT, token_value));
}

t_token *get_next_token(char **input, int *exit_status)
{
	t_token *new_token;
	char *current;

	(void)exit_status;

	current = *input;
	new_token = NULL;

	while (*current && ft_isspace(*current))
		current++;
	if (*current == '\0')
		return (create_token(TOKEN_EOF, NULL));

	if (ft_is_special_character(current))
		return (handle_special_characters(&current, &input));

	if (*current == '$')
		return (handle_dollar_sign(input));

	return (handle_argument(input));
}
