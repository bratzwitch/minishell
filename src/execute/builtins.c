/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:13:54 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/31 09:11:07 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtins(t_prompt *prompt, t_token *tokens, char **env)
{
	if (tokens == NULL)
		return (2);
	if (ft_is_special_token(tokens))
	{
		if(handle_special_tokens(tokens) == -1)
			return (1);
	}
	if (!ft_strcmp(tokens->value, "env"))
		return (handle_env(env));
	else if (!ft_strcmp(tokens->value, "pwd"))
		return (handle_pwd());
	else if (!ft_strcmp(tokens->value, "exit"))
		return (handle_exit(prompt));
	else if (!ft_strcmp(tokens->value, "cd"))
		return (handle_cd(tokens, env));
	else if (!ft_strcmp(tokens->value, "echo"))
		return (handle_echo(tokens));
	else if (!ft_strcmp(tokens->value, "export"))
		return (handle_export(prompt, tokens, &env));
	else if (!ft_strcmp(tokens->value, "unset"))
		return (handle_unset(tokens, env));
	return (2);
}
