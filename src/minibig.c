/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minibig.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:38:21 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/31 12:30:37 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cond_free(t_prompt *prompt, int tr)
{
	if (tr == 1)
	{
		add_history(prompt->input);
		lst_cleanup(&prompt->token_lst, free_token);
	}
	else if (tr == 2)
		add_history(prompt->input);
	else if (tr == 3)
		lst_cleanup(&prompt->token_lst, free_token);
	free(prompt->input);
	return (0);
}

int	isvalidtoken(t_token *t)
{
	if (t->type == TOKEN_PIPE || (count_heredocs(t) && count_pipes(t)))
	{
		ft_putendl_fd("error", STDERR_FILENO);
		return (1);
	}
	while (t)
	{
		if ((t->type == TOKEN_REDIRECT_APPEND || t->type == TOKEN_REDIRECT_IN
				|| t->type == TOKEN_REDIRECT_OUT || t->type == TOKEN_HEREDOC)
			&& (!t->next || t->next->type != TOKEN_ARGUMENT))
		{
			ft_putendl_fd("error", STDERR_FILENO);
			return (1);
		}
		if (t->type == TOKEN_PIPE && (!t->next
				|| t->next->type != TOKEN_ARGUMENT))
		{
			ft_putendl_fd("error", STDERR_FILENO);
			return (1);
		}
		t = t->next;
	}
	return (0);
}

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
