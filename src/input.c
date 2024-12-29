#include "../include/minishell.h"

char	*ft_prompt(void)
{
	char	*input;

	input = readline("minishell$>");
	if (input == NULL) // detect EOF; handle ctrl+D
	{
		write(STDOUT_FILENO, "exit\n", 5);
		printf("vpizdu...\n");
		exit (0);
	}
	return (input);
}

void	handle_input(t_prompt *prompt, char **env)
{
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
	// printf("Command not recognised: %s\n", prompt->input);
	free(prompt->input);
}
