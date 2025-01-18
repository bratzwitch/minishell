/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:47:55 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 13:38:07 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	add_new_var_to_env(char ***env, char *new_var)
{
	int	size;
	int	i;

	size = get_env_size(*env);
	*env = expand_env(*env, size + 1);
	if (!*env)
	{
		perror("Failed to expand env");
		free(new_var);
		return ;
	}
	i = 0;
	while ((*env)[i])
		i++;
	(*env)[i] = new_var;
	(*env)[i + 1] = NULL;
}

void	add_new_var(char ***env, char *new_var, int index)
{
	if (index >= 0)
		replace_existing_var(env, new_var, index);
	else
		add_new_var_to_env(env, new_var);
}

char	*ft_setenv(char *name, char **env)
{
	int		i;
	char	*new_var;
	char	*cut_name;

	if (!name || !ft_strchr(name, '='))
		return (NULL);
	new_var = ft_strdup(name);
	if (!new_var)
		return (NULL);
	cut_name = get_var_name(name);
	if (!cut_name)
		return (NULL);
	i = find_var(cut_name, env);
	free(cut_name);
	add_new_var(&env, new_var, i);
	return (new_var);
}

static int	validate_and_set_var(t_token *token, char ***env)
{
	if (ft_is_valid_identifier(token->value))
	{
		fprintf(stderr, "export: '%s': not a valid identifier\n", token->value);
		return (1);
	}
	ft_setenv(token->value, *env);
	return (0);
}

int	handle_export(t_token *tokens, char **env)
{
	t_token	*tmp;
	int		status;

	tmp = tokens;
	status = 0;
	while (tmp)
	{
		if (validate_and_set_var(tmp, &env))
			status = 1;
		tmp = tmp->next;
	}
	return (status);
}
