#include "../../include/minishell.h"

char *get_env_variable(char **current, char *var_start) // thats execution at this point, no?
{
	char *env_value;
	char *token_value;
	size_t len;

	len = *current - var_start;
	token_value = strndup(var_start, len); // original ft dont forget to replace with libft
	env_value = getenv(token_value);
	free(token_value);
	if (env_value)
		return (env_value);
	else
		return ("");
}

t_token *handle_dollar_sign(char **input)
{
	char *current = *input;
	char *var_start;
	char *env_value;

	current++;
	if (*current == '?')
	{
		*input = current + 1;
		return (create_token(TOKEN_EXIT_STATUS, ft_itoa(received_sig)));
	}
	var_start = current;
	while (ft_isalnum(*current) || *current == '_')
		current++;
	env_value = get_env_variable(&current, var_start);
	while (*current && ft_isspace(*current))
		current++;
	*input = current;
	if (env_value)
		return (create_token(TOKEN_ENV_VAR, env_value));
	else
		return (create_token(TOKEN_ENV_VAR, ""));
}
