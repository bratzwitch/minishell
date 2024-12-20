#include "../include/minishell.h"

void	handle_input(t_prompt *prompt, char **env)
{
	tokenise(prompt);

	if (prompt->input[0] == '\0')
	{
		free(prompt->input);
		return ;
	}
	if (handle_builtin_cmds(prompt, env))
	{
		free(prompt->input);
		return ;
	}
	printf("Command not recognised: %s\n", prompt->input);
	free(prompt->input);
}
