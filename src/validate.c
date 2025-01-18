#include "../include/minishell.h"

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
		{
			free(dirs);
			return (NULL);
		}
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

char *validator(char *cmd_name)
{
	char *path;

	if (!strncmp(cmd_name, "../", 3) || !strncmp(cmd_name, "./", 2) || !strncmp(cmd_name, "/", 1))
	{
		if (access(cmd_name, X_OK) == 0)
			return (ft_strdup(cmd_name));
		else
		{
			perror("error");
			g_received_sig = 127;
			return (NULL);
		}
	}
	path = find_command(cmd_name, getenv("PATH"));
	if (!path)
	{
		// free(path);
		g_received_sig = 127;
		return (NULL);
	}
	return (path);
}
