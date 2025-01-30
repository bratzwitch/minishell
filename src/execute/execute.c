/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:14:00 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/30 12:39:41 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute(t_token *tokens, char *path, char **env)
{
	char	**args;
	char	*path_exec;

	if (ft_is_special_token(tokens))
	{
		if(handle_special_tokens(tokens) == -1)
			return (-1);
	}
	args = lst_to_arr(tokens);
	if (path)
		path_exec = path;
	else
	{
		path_exec = validator(tokens->value);
		if (!path_exec)
			g_received_sig = builtins(NULL, tokens, env);
	}
	if(path_exec != NULL)
		execve(path_exec, args, env);
	perror("execve");
	exit(-1);
}
