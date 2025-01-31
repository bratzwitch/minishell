/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:01:18 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/31 12:31:10 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_received_sig = 0;

int	builtins_handle(t_prompt *prompt)
{
	if (save_stdinout(&prompt->fdin_copy, &prompt->fdout_copy) == -1)
		return (1);
	if (!prompt->token_lst || !prompt->token_lst->value)
	{
		ft_putendl_fd("Error: Invalid token in builtins", STDERR_FILENO);
		restore_stdinout(&prompt->fdin_copy, &prompt->fdout_copy);
		return (1);
	}
	g_received_sig = builtins(prompt, prompt->token_lst, prompt->env_copy);
	if (!g_received_sig || g_received_sig == 1)
	{
		restore_stdinout(&prompt->fdin_copy, &prompt->fdout_copy);
		return (1);
	}
	return (0);
}

void	mini_family(t_prompt *prompt)
{
	pid_t	pid;

	pid = 0;
	pid = create_child_process();
	if (pid == 0)
		handle_child_process(prompt, prompt->env_copy);
	else
		handle_parent_process(pid, &prompt->exit_status, prompt);
}

void	handle_single_cmd(t_prompt *prompt)
{
	if (builtins_handle(prompt) == 1)
		return ;
	prompt->path = validator(prompt->token_lst->value);
	if (!prompt->path && !ft_is_special_character(prompt->input))
	{
		if (ft_strcmp(prompt->token_lst->value, " ") != 0)
		{
			ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
			ft_putendl_fd(prompt->token_lst->value, STDERR_FILENO);
		}
		restore_stdinout(&prompt->fdin_copy, &prompt->fdout_copy);
		return ;
	}
	else
		mini_family(prompt);
	free(prompt->path);
	lst_cleanup(&prompt->token_lst, free_token);
	restore_stdinout(&prompt->fdin_copy, &prompt->fdout_copy);
}

int	init(t_prompt *prompt)
{
	prompt->input = ft_prompt(prompt);
	if (!prompt->input)
		return (1);
	if (ft_isallspace(prompt->input))
		return (free(prompt->input), 0);
	prompt->token_lst = lexer(prompt->input);
	if (isvalidtoken(prompt->token_lst) == 1)
		return (cond_free(prompt, 1));
	if (prompt->token_lst)
	{
		if (is_pipe(prompt->token_lst))
		{
			piping(prompt);
			return (cond_free(prompt, 2));
		}
		else
			handle_single_cmd(prompt);
	}
	else if (!prompt->token_lst)
		return (cond_free(prompt, 3));
	return (cond_free(prompt, 1));
}

int	main(int argc, char **argv, char **env)
{
	t_prompt	prompt;

	(void)argc;
	(void)argv;
	prompt.path = NULL;
	prompt.env_copy = copy_env(env);
	setup_handlers();
	while (1)
	{
		if (init(&prompt) == 1)
			break ;
	}
	return (0);
}
