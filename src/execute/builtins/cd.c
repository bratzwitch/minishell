/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:47:46 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/31 11:42:21 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*extract_var(char *name, char **env)
{
	char	*result;
	int		i;

	i = find_var(name, env);
	result = ft_strchr(env[i], '=');
	result = result + 1;
	return (result);
}

t_token	*assemble_name(char *path, char **env)
{
	t_token	*new_lst;
	char	*new_oldpwd;
	char	*new_pwd;

	new_lst = NULL;
	new_lst = NULL;
	new_oldpwd = format_env_var("OLDPWD", extract_var("PWD", env));
	add_token(&new_lst, create_token(0, new_oldpwd));
	new_pwd = format_env_var("PWD", path);
	add_token(&new_lst, create_token(0, new_pwd));
	return (new_lst);
}

static int	change_directory(char **path)
{
	if (chdir(*path) == -1)
	{
		perror("minishell: cd");
		return (1);
	}
	*path = getcwd(NULL, 0);
	if (!*path)
	{
		perror("minishell: pwd");
		return (1);
	}
	return (0);
}

static char	*resolve_path(t_token *token, char **env)
{
	char	*home;
	int		index;

	if (!token->next || !ft_strcmp(token->next->value, "~"))
	{
		home = getenv("HOME");
		if (!home && env)
		{
			index = find_var("HOME", env);
			if (index >= 0)
				home = ft_strchr(env[index], '=') + 1;
		}
		if (!home)
		{
			perror("minishell: cd: HOME not set");
			return (NULL);
		}
		return (home);
	}
	return (token->next->value);
}

int	handle_cd(t_token *token, char **env)
{
	char	*path;
	t_token	*var_lst;

	if (count_tokens(token) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	path = resolve_path(token, env);
	if (!path)
		return (1);
	if (change_directory(&path))
		return (1);
	var_lst = assemble_name(path, env);
	free(path);
	if (!var_lst)
		return (1);
	handle_export(NULL, var_lst, &env);
	lst_cleanup(&var_lst, free_token);
	return (0);
}
