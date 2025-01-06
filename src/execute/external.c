#include "../../include/minishell.h"

char *build_path(char *dir, char *cmd_name)
{
	char *with_slash;
	char *full_path;

	with_slash = ft_strjoin(dir, "/");
	if (!with_slash)
		return (NULL);
	full_path = ft_strjoin(with_slash, cmd_name);
	free(with_slash);
	return (full_path);
}

char *find_command(char *cmd_name, char *env_path)
{
	char **dirs;
	char *full_path;
	int i;

	if (!env_path)
		return (NULL);
	dirs = ft_split(env_path, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = build_path(dirs[i], cmd_name);
		if (!full_path)
			break;
		if (access(full_path, X_OK) == 0)
		{
			ft_free(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free(dirs);
	return (NULL);
}

int validator(t_prompt *prompt, char *cmd_name, char **env)
{
	(void)env;
	prompt->path = find_command(cmd_name, getenv("PATH")); // dont forget to free later
	if (!prompt->path)
	{
		printf("Command not recognised: %s\n", cmd_name);
		return (127);
	}
	printf("Found the command at: %s\n", prompt->path);
	// free(prompt->path);
	return(0);
}

int execute(t_prompt *prompt, char *cmd_name, char **env)
{
	char *arg_single[2] = {cmd_name, NULL};

	execve(prompt->path, arg_single, env);
	free(prompt->path);
	return(0);
}
