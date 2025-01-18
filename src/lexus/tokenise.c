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
	char *current = *input;
	char *final_str = ft_calloc(1, 1);
	char *start;
	char quote;

	if (!final_str)
	{
		free(final_str);
		free(current);
		return (NULL);
	}
	while (*current && !ft_isspace(*current))
	{
		if (ft_is_quotes(current))
		{
			quote = *current;
			if (quote == '\'')
				final_str = handle_single_quotes(&current, final_str);
			else if (quote == '\"')
				final_str = handle_double_quote(&current, final_str);
			if (!final_str)
			{
				free(final_str);
				return (NULL);
			}
		}
		else if (*current == '$' && *(current + 1))
		{
			final_str = dollar(&current, final_str, &current);
			if (!final_str)
			{
				free(final_str);
				free(current);
				return NULL;
			}
		}
		else
		{
			start = current;
			while (*current && !ft_isspace(*current) && !ft_is_special_character(current) && !ft_is_quotes(current))
				current++;
			final_str = append_to_final_str(final_str, start, current - start);
			if (!final_str)
			{
				free(final_str);
				free(current);
				return NULL;
			}
		}
	}
	while (*current && ft_isspace(*current))
		current++;
	*input = current;
	return (create_token(TOKEN_ARGUMENT, final_str));
}

t_token *get_next_token(char **input)
{
	char *current;

	current = *input;
	while (*current && ft_isspace(*current))
		current++;
	if (*current == '\0')
		return (create_token(TOKEN_EOF, NULL));
	if (ft_is_special_character(current))
		return (handle_special_characters(&current, input));
	return (handle_argument(input));
}
