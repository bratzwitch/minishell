
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

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
	// Ignore SIGQUIT signal
	signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		// Prompt displayed by readline
		input = readline("minishell$>");
		if (input == NULL)
		{
			// Exit on Ctrl+D (EOF)
			printf("vpizdu....\n");
			break ;
		}
		
		if (input[0] == '\0')
		{
			// Skip empty input (after hitting backspace or space)
			free(input);
			continue;
		}
		
		// Handle specific commands
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
			path = getcwd(NULL, 0); // Use NULL to dynamically allocate memory
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

		// You can add other logic to handle commands here
		free(input);
	}

	return (0);
}
