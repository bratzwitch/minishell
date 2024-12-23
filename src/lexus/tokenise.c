#include "../../include/minishell.h"
# include <string.h>

t_token *create_token(t_token_type type, char *value)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
	{
		perror("?????");
		exit(1);
	}
	new_token->type = type;
	if (value)
		new_token->value = value;
	else
		new_token->value = NULL;
	return (new_token);
}

t_token *get_next_token(char **input, int *exit_status)
{
	t_token *new_token;
	char *current;
	char *token_value;
	char *start;

	(void)exit_status;

	start = *input;
	current = *input;
	new_token = NULL;

	while (*current && ft_isspace(*current))
		current++;
	if (*current == '\0')
		return (create_token(TOKEN_EOF, NULL));

	new_token = handle_special_characters(&current); // handles redirections and a pipe
	if (new_token)
	{
		*input = current;
		return (new_token);
	}

	if (*current == '$')
		return (handle_dollar_sign(input));

	while (*current && !ft_isspace(*current) && *current != '<' && *current != '>' && *current != '|' && *current != '$') // ??
		current++;
	
	*input = current;
	token_value = strndup(start, current - start);
	// if (!token_value)
	// 	return (NULL);
	new_token = create_token(TOKEN_ARGUMENT, token_value);
	// if (!new_token)
	// 	free (token_value);
	return (new_token);
}

// todo
// ya ebu chtoli
// nado teper tokeni use in parsing a takze fix norm hovna
// zaebalsya jsem

// yeba 22.12.24:
// testy delam