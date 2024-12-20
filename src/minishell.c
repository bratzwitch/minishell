#include "../include/minishell.h"

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
