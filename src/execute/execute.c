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
		{
			free(dirs);
			return(NULL);
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

	path = find_command(cmd_name, getenv("PATH")); // dont forget to free later
	if (!path)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

int execute(t_token *tokens, char *path, char **env)
{
	char **args;
	char *path_exec;

	args = lst_to_arr(tokens);
	if (path)
		path_exec = path;
	else
		path_exec = validator(tokens->value);
	execve(path_exec, args, env);
	perror("execve");
	exit(1);
}
