#include "../include/minishell.h"

void	sig_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\nminishell$>", 12);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *input;
	char *path;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		input = readline("minishell$>");
		if (input == NULL)
		{
			printf("vpizdu....\n");
			break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		if (!strcmp(input, "env"))
		{
			while (*env)
			{
				printf("%s\n", *env);
				env++;
			}
			continue ;
		}
		if (!strcmp(input, "pwd"))
		{
			path = getcwd(NULL, 0);
			if (path != NULL)
			{
				printf("%s\n", path);
				free(path);
			}
			continue ;
		}
		if (!strcmp(input, "exit"))
		{
			printf("vpizdu.....\n");
			free(input);
			break ;
		}
		free(input);
	}
	return (0);
}
