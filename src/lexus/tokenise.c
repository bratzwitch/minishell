#include "../../include/minishell.h"

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
	{
		perror("?????");
		exit(1);
	}
	new_token->type = type;
	if (value)
	{
		new_token->value = ft_strdup(value);
	}
	else
	{
		new_token->value = NULL;
	}
	return (new_token);
}

void	free_token(t_token *t)
{
	if (t)
	{
		if (t->value)
			free(t->value);
		free(t);
	}
}

t_token	*get_next_token(char **input, char **env, int *exit_status)
{
	char	*start;
	char	*current;
	char	*token_value;
	t_token	*new_token;
	char	*var_start;
	size_t	len;
	char	*env_value;

	(void)env;
	(void)exit_status;
	start = *input;
	current = *input;
	token_value = NULL;
	new_token = NULL;
	while (*current && ft_isspace(*current))
	{
		current++;
	}
	if (*current == '\0')
	{
		return (create_token(TOKEN_EOF, NULL));
	}
	if (*current == '<')
	{
		if (*(current + 1) == '<')
		{
			*input = current + 2;
			return (create_token(TOKEN_HEREDOC, "<<"));
		}
		*input = current + 1;
		return (create_token(TOKEN_REDIRECT_IN, "<"));
	}
	else if (*current == '>')
	{
		if (*(current + 1) == '>')
		{
			*input = current + 2;
			return (create_token(TOKEN_REDIRECT_APPEND, ">>"));
		}
		*input = current + 1;
		return (create_token(TOKEN_REDIRECT_OUT, ">"));
	}
	else if (*current == '|')
	{
		*input = current + 1;
		return (create_token(TOKEN_PIPE, "|"));
	}
	if (*current == '$')
	{
		current++;
		if (*current == '?')
		{
			*input = current + 1;
			return (create_token(TOKEN_EXIT_STATUS, "$?"));
		}
		var_start = current;
		while (isalnum(*current) || *current == '_')
		{
			current++;
		}
		len = current - var_start;
		token_value = strndup(var_start, len);
		*input = current;
		env_value = getenv(token_value);
		if (env_value)
		{
			return (create_token(TOKEN_ENV_VAR, env_value));
		}
		else
		{
			return (create_token(TOKEN_ENV_VAR, ""));
		}
	}
	while (*current && !ft_isspace(*current) && *current != '<'
		&& *current != '>' && *current != '|' && *current != '$')
	{
		current++;
	}
	token_value = strndup(start, current - start);
	*input = current;
	return (create_token(TOKEN_ARGUMENT, token_value));
}

void	lexer(char *input, char **env)
{
	t_token	*t;
	int		exit_status;

	t = NULL;
	exit_status = 0;
	t = get_next_token(&input, env, &exit_status);
	while (t->type != TOKEN_EOF)
	{
		if (t->type == TOKEN_ERROR)
		{
			printf("Nope bye\n");
			break ;
		}
		printf("Token Type: %d, Token Value: %s\n", t->type, t->value);
		free_token(t);
		t = get_next_token(&input, env, &exit_status);
	}
	free_token(t);
}
// todo
// ya ebu chtoli
// nado teper tokeni use in parsing a takze fix norm hovna
// zaebalsya jsem