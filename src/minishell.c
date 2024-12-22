#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_prompt	prompt;
	(void)argc;
	(void)argv;
	(void)env;

	setup_handlers();
	
	while (1)
	{
		prompt.input = ft_prompt();
		lexer(prompt.input);
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
