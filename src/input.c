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

void	handle_input(t_prompt *prompt, char *args[], char **env)
{
	if (prompt->input[0] == '\0')
	{
		printf("input is zero just like the number of times i hit the gym this week\n");
		free(prompt->input);
		return ;
	}
	else if (handle_builtin_cmds(prompt, args, env) == 0)
	{
		free(prompt->input);
		return ;
	}
	free(prompt->input);
}
