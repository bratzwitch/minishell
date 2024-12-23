#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_prompt	prompt;
	pid_t		id;

	(void)argc;
	(void)argv;
	
	setup_handlers();
	while (1)
	{
		prompt.input = ft_prompt();
		id = fork();
		if (id == -1)
		{
			perror("no fork today");
			break ;
		}
		if (id == 0)
		{
			lexer(prompt.input);
			if (prompt.input == NULL)
			{
				printf("vpizdu....\n");
				break ;
			}
			add_history(prompt.input);
			handle_input(&prompt, env);
			exit(0);
		}
		else
		{
			add_history(prompt.input);
			waitpid(id, NULL, 0);
			printf("%d\n",id);
			printf("ZzZzZz...\n");
		}
	}
	free(prompt.input);
	return (0);
}
