#include "../include/minishell.h"

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
	if (!ft_strcmp(prompt->input, "ls"))
	{
		execve("/usr/bin/ls", &prompt->input, env);
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
		return (0);
	}
	return (0);
}
