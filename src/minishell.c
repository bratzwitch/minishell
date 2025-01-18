/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:01:18 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 14:51:58 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_received_sig = 0;

int	builtins_handle(t_prompt *prompt)
{
	if (save_stdinout(&prompt->fdin_copy, &prompt->fdout_copy) == -1)
		return (1);
	g_received_sig = builtins(prompt, prompt->token_lst, prompt->env_copy);
	if (!g_received_sig || g_received_sig == 1)
	{
		restore_stdinout(&prompt->fdin_copy, &prompt->fdout_copy);
		return (1);
	}
	return (0);
}

void	handle_single_cmd(t_prompt *prompt)
{
	pid_t	pid;

	pid = 0;
	if (builtins_handle(prompt) == 1)
		return ;
	prompt->path = validator(prompt->token_lst->value);
	if (!prompt->path && !ft_is_special_character(prompt->input))
	{
		printf("minishell: command not found: %s\n", prompt->token_lst->value);
		restore_stdinout(&prompt->fdin_copy, &prompt->fdout_copy);
		return ;
	}
	else
	{
		pid = create_child_process();
		if (pid == 0)
			handle_child_process(prompt, prompt->env_copy);
		else
			handle_parent_process(pid, &prompt->exit_status, prompt);
	}
	free(prompt->path);
	restore_stdinout(&prompt->fdin_copy, &prompt->fdout_copy);
}

int	init(t_prompt *prompt)
{
	prompt->input = ft_prompt(prompt);
	if (!prompt->input)
		return (1);
	if (prompt->input[0] == '|')
	{
		printf("parse error near `|'\n");
		ft_free(prompt->env_copy);
		return (1);
	}
	prompt->token_lst = lexer(prompt->input);
	if (prompt->token_lst)
	{
		if (is_pipe(prompt->token_lst))
			piping(prompt);
		else
			handle_single_cmd(prompt);
	}
	add_history(prompt->input);
	free(prompt->input);
	lst_cleanup(&prompt->token_lst, free_token);
	return (0);
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
