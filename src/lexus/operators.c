#include "../../include/minishell.h"

t_token *handle_input_redirection(char **input)
{
	char *current = *input;

	if (*(current + 1) == '<')
	{
		*input = current + 2;
		return (create_token(TOKEN_HEREDOC, "<<"));
	}
	*input = current + 1;
	return (create_token(TOKEN_REDIRECT_IN, "<"));
}

t_token *handle_output_redirection(char **input)
{
	char *current = *input;

	if (*(current + 1) == '>')
	{
		*input = current + 2;
		return (create_token(TOKEN_REDIRECT_APPEND, ">>"));
	}
	*input = current + 1;
	return (create_token(TOKEN_REDIRECT_OUT, ">"));
}

t_token *handle_pipe(char **input)
{
	*input = *input + 1;
	return (create_token(TOKEN_PIPE, "|"));
}

t_token *handle_special_characters(char **input)
{
	char *current = *input;

	if (*current == '<')
		return (handle_input_redirection(input));
	else if (*current == '>')
		return (handle_output_redirection(input));
	else if (*current == '|')
		return (handle_pipe(input));
	return (NULL);
}
