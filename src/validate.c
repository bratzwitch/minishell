/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:46:57 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 14:42:08 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*build_path(char *dir, char *cmd_name)
{
	char	*with_slash;
	char	*full_path;

	with_slash = ft_strjoin(dir, "/");
	if (!with_slash)
		return (NULL);
	full_path = ft_strjoin(with_slash, cmd_name);
	free(with_slash);
	return (full_path);
}

char	**split_env_path(char *env_path)
{
	if (!env_path)
		return (NULL);
	return (ft_split(env_path, ':'));
}

char	*check_command_in_dir(char *dir, char *cmd_name)
{
	char	*full_path;

	full_path = build_path(dir, cmd_name);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*find_command(char *cmd_name, char *env_path)
{
	char	**dirs;
	int		i;
	char	*full_path;

	dirs = split_env_path(env_path);
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = check_command_in_dir(dirs[i], cmd_name);
		if (full_path)
		{
			ft_free(dirs);
			return (full_path);
		}
		i++;
	}
	ft_free(dirs);
	return (NULL);
}

char	*validator(char *cmd_name)
{
	char	*path;

	if (!strncmp(cmd_name, "../", 3) || !strncmp(cmd_name, "./", 2)
		|| !strncmp(cmd_name, "/", 1))
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
		g_received_sig = 127;
		return (NULL);
	}
	return (path);
}
