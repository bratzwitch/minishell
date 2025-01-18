/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:47:55 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 17:50:46 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void add_new_var_to_env(t_prompt *prompt, char ***env, char *new_var)
{
	int size;
	char **new_env;

	size = get_env_size(*env);
	new_env = expand_env(*env, size + 1);
	if (!*new_env)
	{
		perror("Failed to expand env");
		free(new_var);
		return;
	}
	*env = new_env;
	(*env)[size] = new_var;
	(*env)[size + 1] = NULL;
	if (prompt)
		prompt->env_copy = *env;
}

char *ft_setenv(t_prompt *prompt, char *name, char ***env)
{
	int i;
	char *new_var;
	char *cut_name;

	if (!name || !ft_strchr(name, '='))
		return (NULL);
	new_var = ft_strdup(name);
	if (!new_var)
		return (NULL);
	cut_name = get_var_name(name);
	if (!cut_name)
		return (NULL);
	i = find_var(cut_name, *env);
	free(cut_name);
	if (i >= 0)
	{
		free((*env)[i]);
		(*env)[i] = new_var;
	}
	else
		add_new_var_to_env(prompt, env, new_var);
	return (new_var);
}

static int validate_and_set_var(t_prompt *prompt, t_token *token, char ***env)
{
	if (ft_is_valid_identifier(token->value))
	{
		ft_putendl_fd("minishell: export: not a valid identifier", STDERR_FILENO);
		return (1);
	}
	ft_setenv(prompt, token->value, env);
	return (0);
}

int handle_export(t_prompt *prompt, t_token *tokens, char ***env)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		if (validate_and_set_var(prompt, tmp, env))
			g_received_sig = 1;
		tmp = tmp->next;
	}
	return (g_received_sig);
}
