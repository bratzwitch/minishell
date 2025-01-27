/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:00:07 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/27 14:41:27 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

pid_t	create_child_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}

void	handle_child_process(t_prompt *prompt, char **env)
{
	setup_dfl_signals();
	if(execute(prompt->token_lst, prompt->path, env) == -1)
	{
		cleanup(prompt);
		printf("\nbro\n");
		exit(1);
	}
	printf("No food today: %s\n", strerror(errno));
	cleanup(prompt);
	exit(1);
}

void	handle_parent_process(pid_t id, int *exit_status, t_prompt *prompt)
{
	ignore_signals();
	add_history(prompt->input);
	waitpid(id, exit_status, 0);
	setup_handlers();
	if (WIFEXITED(*exit_status))
		g_received_sig = WEXITSTATUS(*exit_status);
	else if (WIFSIGNALED(*exit_status))
		g_received_sig = 128 + WTERMSIG(*exit_status);
	else if (WIFSTOPPED(*exit_status))
		g_received_sig = WSTOPSIG(*exit_status);
	if (WIFSIGNALED(*exit_status) && WTERMSIG(*exit_status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}
