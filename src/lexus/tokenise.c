#include "../../include/minishell.h"

t_token *create_token(enum e_token_type type, char *value)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		printf("Error creating a token: %s\n", strerror(errno));
		return (NULL);
	}
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

t_token *handle_argument(char **input)
{
	char *current;
	char *start;
	char *token_value;

	current = *input;
	start = current;
	while (*current && !ft_isspace(*current) && !ft_is_special_character(current))
		current++;
	token_value = strndup(start, current - start);
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

bool is_quote(char *input)
{
	int i = 0;

	while (input[i])
	{
		if (input[i] == '\'')
		{
			return (true);
		}
		i++;
	}
	return (false);
}

t_token *get_next_token(char **input)
{
	char *current;

	current = *input;
	if ()
	{
		if (*current == '\'')
			return (handle_single_quotes_argument(input));
		if (*current == '\"')
			return (handle_double_quotes_argument(input));
	}
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
