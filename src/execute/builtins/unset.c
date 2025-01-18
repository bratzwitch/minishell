/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:47:58 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 18:26:30 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	find_var(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], name, strlen(name)) == 0) // slava
			return (i);
		i++;
	}
	return (-1);
}

int	ft_unsetenv(char *name, char **env)
{
	int	i;

	if (!name || !*name || strchr(name, '=') != NULL) // slava
	{
		ft_putendl_fd("minishell: unsetenv: invalid variable name", STDERR_FILENO);
		return (-1);
	}
	i = find_var(name, env);
	if (i < 0)
		return (1);
	free(env[i]);
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
	return (0);
}

int	handle_unset(t_token *tokens, char **env)
{
	t_token	*tmp;

	tmp = tokens;
	if (!tmp->next)
	{
		ft_putendl_fd("minishell: unset: not enough arguments", STDERR_FILENO);
		return(1);
	}
	while (tmp && tmp->next)
	{
		if (ft_unsetenv(tmp->next->value, env) != 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
