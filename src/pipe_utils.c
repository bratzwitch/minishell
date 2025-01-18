/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:00:35 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 14:00:36 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_pipes(t_token *token_lst)
{
	t_token	*temp;
	int		pipes;

	pipes = 0;
	temp = token_lst;
	while (temp != NULL)
	{
		if (temp->type == TOKEN_PIPE)
			pipes += 1;
		temp = temp->next;
	}
	return (pipes);
}

int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("Error creating pipe");
		return (-1);
	}
	return (0);
}

void	create_pipes(int i, int pipe_count, int fd[2])
{
	if (i < pipe_count)
	{
		if (create_pipe(fd) == -1)
			exit(1);
	}
}

void	wait_for_children(int child_count)
{
	int	i;
	int	exit_status;

	i = 0;
	while (i < child_count)
	{
		if (wait(&exit_status) > 0)
		{
			if (WIFEXITED(exit_status))
				g_received_sig = WEXITSTATUS(exit_status);
			else if (WIFSIGNALED(exit_status))
				g_received_sig = 128 + WTERMSIG(exit_status);
			else if (WIFSTOPPED(exit_status))
				g_received_sig = WSTOPSIG(exit_status);
		}
		if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
}
