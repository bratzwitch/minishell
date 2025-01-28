/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibig.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:38:21 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/28 11:25:22 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_prompt(t_prompt *prompt)
{
	char	*input;

	input = NULL;
	if (isatty(STDIN_FILENO))
		input = readline("minishell$>");
	if (input == NULL)
	{
		ft_putendl_fd("Vp*zdu brother.(remove once done)", 1);
		ft_free(prompt->env_copy);
		rl_clear_history();
		exit(g_received_sig);
	}
	return (input);
}

int	save_stdinout(int *fdin_copy, int *fdout_copy)
{
	*fdin_copy = dup(STDIN_FILENO);
	if (fdin_copy && *fdin_copy == -1)
	{
		perror("Error redirecting input.");
		close(*fdin_copy);
		return (-1);
	}
	*fdout_copy = dup(STDOUT_FILENO);
	if (fdout_copy && *fdout_copy == -1)
	{
		perror("Error redirecting input.");
		close(*fdout_copy);
		return (-1);
	}
	return (0);
}

void	restore_stdinout(int *fdin_copy, int *fdout_copy)
{
	if (fdin_copy)
	{
		dup2(*fdin_copy, STDIN_FILENO);
		close(*fdin_copy);
	}
	if (fdout_copy)
	{
		dup2(*fdout_copy, STDOUT_FILENO);
		close(*fdout_copy);
	}
}
