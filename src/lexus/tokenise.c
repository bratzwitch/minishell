#include "../../include/minishell.h"

t_token *create_token(t_token_type type, char *value)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		printf("Error creating a token: %s\n", strerror(errno));
		return (NULL);
	}
	if (value)
	{
		new_token->type = type;
		new_token->value = value;
	}
	else
	{
		new_token->type = TOKEN_ERROR;
		new_token->value = NULL;
	}
	return (new_token);
}

// leaves the input pointer to the next char after the command - points to the space
t_token *handle_argument(char **input)
{
	char *current = *input;
	char *start = current;
	char *token_value;

	while (*current && !ft_isspace(*current) && !ft_is_special_character(current))
		current++;
	token_value = strndup(start, current - start); // original ft dont forget to replace with libft
	if (!token_value)
	{
		printf("Memory allocation failed: %s\n", strerror(errno));
		return (NULL);
	}
	while (*current && ft_isspace(*current))
		current++;
	*input = current;
	return (create_token(TOKEN_ARGUMENT, token_value));
}

t_token *get_next_token(char **input, int *exit_status)
{
	char *current;
	(void)exit_status;

	current = *input;
	while (*current && ft_isspace(*current))
		current++;
	if (*current == '\0')
		return (create_token(TOKEN_EOF, NULL));
	if (ft_is_special_character(current))
		return (handle_special_characters(&current, input));
	if (*current == '$')
		return (handle_dollar_sign(input));
	return (handle_argument(input));
}
// (gdb) set follow-fork-mode child / parent
