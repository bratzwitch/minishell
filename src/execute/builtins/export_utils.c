/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:21:44 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/23 12:00:44 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_is_valid_identifier(char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (true);
	name++;
	while (*name && *name != '=')
	{
		if (!(ft_isalpha(*name)) && *name != '_')
			return (true);
		name++;
	}
	return (false);
}

char	*get_var_name(const char *name)
{
	char	*equal_sign;
	size_t	len;

	equal_sign = ft_strchr(name, '=');
	if (!equal_sign)
		return (NULL);
	len = equal_sign - name;
	return (strndup(name, len));
}

char **expand_env(char **env, int new_size)
{
    char **new_env;
    int i;

    new_env = malloc((new_size + 1) * sizeof(char *));
    if (!new_env)
        return (NULL);
    i = 0;
    while (env[i])
    {
        new_env[i] = ft_strdup(env[i]);
        if (!new_env[i])
        {
            while (i > 0)
                free(new_env[--i]);
            free(new_env);
            return (NULL);
        }
        i++;
    }
    new_env[i] = NULL;
	ft_free(env);
    return (new_env);
}

int	get_env_size(char **env)
{
	int	size;

	size = 0;
	while (env && env[size])
		size++;
	return (size);
}
