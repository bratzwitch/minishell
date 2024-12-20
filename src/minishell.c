#include "../include/minishell.h"

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
	printf("Command not recognised: %s\n", prompt->input);
	free(prompt->input);
}

char	*ft_prompt(void)
{
	char	*input;
	input = readline("minishell$>");
	if (input == NULL || atoi(input) == EOF)
	{
		printf("vpizdu....\n");
		exit(0);
	}
	return (input);
}

int	main(int argc, char **argv, char **env)
{
	t_prompt	prompt;

	(void)argc;
	(void)argv;

	setup_handlers();
	while (1)
	{
		prompt.input = ft_prompt();
		if (prompt.input == NULL)
		{
			printf("vpizdu....\n");
			break ;
		}
		add_history(prompt.input);
		handle_input(&prompt, env);
	}
	return (0);
}
