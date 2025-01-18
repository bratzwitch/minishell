/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:13:54 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 18:19:43 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtins(t_prompt *prompt, t_token *tokens, char **env)
{
	if (tokens == NULL)
		return (2);
	if (ft_is_special_token(tokens))
		handle_special_tokens(tokens);
	if (!strcmp(tokens->value, "env"))
		return (handle_env(env));
	else if (!strcmp(tokens->value, "pwd"))
		return (handle_pwd());
	else if (!strcmp(tokens->value, "exit"))
		return (handle_exit(prompt));
	else if (!strcmp(tokens->value, "cd"))
		return (handle_cd(tokens, env));
	else if (!strcmp(tokens->value, "echo"))
		return (handle_echo(tokens));
	else if (!strcmp(tokens->value, "export"))
		return (handle_export(prompt, tokens, &env));
	else if (!strcmp(tokens->value, "unset"))
		return (handle_unset(tokens, env));
	return (2);
}
