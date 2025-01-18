/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:39:19 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 14:04:06 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_variable(char **current, char *var_start)
{
	char	*env_value;
	char	*token_value;
	size_t	len;

	len = *current - var_start;
	token_value = strndup(var_start, len);
	env_value = getenv(token_value);
	free(token_value);
	if (env_value)
		return (env_value);
	else
		return ("");
}

char	*process_dollar(char **current)
{
	char	*var_start;
	char	*env_value;

	var_start = *current + 1;
	if (*var_start == '?')
	{
		*current = var_start + 1;
		return (ft_itoa(g_received_sig));
	}
	if (!ft_isalnum(*var_start) && *var_start != '_')
	{
		*current = var_start;
		return ("$");
	}
	while (ft_isalnum(*var_start) || *var_start == '_')
		var_start++;
	env_value = get_env_variable(&var_start, *current + 1);
	*current = var_start;
	return (env_value);
}

char	*dollar(char **current, char *final_str, char **start)
{
	char	*temp;
	char	*env_value;

	temp = append_to_final_str(final_str, *start, *current - *start);
	env_value = process_dollar(current);
	final_str = ft_strjoin(temp, env_value);
	free(temp);
	free(env_value);
	*start = *current;
	return (final_str);
}
