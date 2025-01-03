#include "../../include/minishell.h"

t_token	*handle_input_redirection(char **current)
{
	char	*temp;

	temp = *current;
	if (*(temp + 1) == '<')
	{
		*current = temp + 2;
		return (create_token(TOKEN_HEREDOC, "<<"));
	}
	*current = temp + 1;
	return (create_token(TOKEN_REDIRECT_IN, "<"));
}

t_token	*handle_output_redirection(char **current)
{
	char	*temp;

	temp = *current;
	if (*(temp + 1) == '>')
	{
		*current = temp + 2;
		return (create_token(TOKEN_REDIRECT_APPEND, ">>"));
	}
	*current = temp + 1;
	return (create_token(TOKEN_REDIRECT_OUT, ">"));
}

t_token	*handle_pipe(char **current)
{

	*current = *current + 1;
	return (create_token(TOKEN_PIPE, "|"));
}

t_token	*handle_special_characters(char **current, char **input)
{
	char	*temp;
	t_token	*new_token;

	temp = *current;
	new_token = NULL;
	if (*temp == '<')
		new_token = handle_input_redirection(current);
	else if (*temp == '>')
		new_token = handle_output_redirection(current);
	else if (*temp == '|')
	{
		new_token = handle_pipe(current);
	}
	if (!new_token)
		return (NULL);
	while (**current && ft_isspace(**current))
		*current = *current + 1;
	*input = *current;
	return (new_token);
}
