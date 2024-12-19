#include "../include/minishell.h"

void	sig_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}

int	handle_builtin_cmds(t_prompt *prompt, char **env)
{
	if (!strcmp(prompt->input, "env"))
	{
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
		return (1);
	}
	if (!strcmp(prompt->input, "pwd"))
	{
		prompt->path = getcwd(NULL, 0);
		if (prompt->path != NULL)
		{
			printf("%s\n", prompt->path);
			free(prompt->path);
			return (1);
		}
	}
	if (!strcmp(prompt->input, "exit"))
	{
		printf("vpizdu.....\n");
		free(prompt->input);
		exit(0);
	}
	return (0);
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
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
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
