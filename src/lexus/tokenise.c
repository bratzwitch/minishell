#include "../../include/minishell.h"

void tokenise(t_prompt *prompt)
{
	char *token;
	int i = 0;

	token = strtok(prompt->input, " ");
	while (token != NULL)
	{
		prompt->all_tokens[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
}