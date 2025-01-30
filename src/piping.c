/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:00:15 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/30 11:02:43 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool no_nl(int flag)
{
	static bool nl = 0;

	if (flag == 3)
		return(nl);
	else
	{
		nl = flag;
		return(nl);
	}
}

void	handle_child_process_pipe(t_pipe *pipe, char **env)
{
	if (pipe->prev_pipe != -1)
		restore_stdinout(&pipe->prev_pipe, NULL);
	if (pipe->i < pipe->pipe_count)
		restore_stdinout(NULL, &pipe->fd[1]);
	else
		close(pipe->fd[1]);
	close(pipe->fd[0]);
	no_nl(1);
	if (validator(pipe->list1->value))
	{
		if (execute(pipe->list1, NULL, env) == -1)
		{
			ft_free(env);
			if (pipe->list1)
				lst_cleanup(&pipe->list1, free_token);
			if (pipe->current_tokens)
				lst_cleanup(&pipe->current_tokens, free_token);
		}
	}
	ft_free(env);
	if (pipe->list1)
		lst_cleanup(&pipe->list1, free_token);
	if (pipe->current_tokens)
		lst_cleanup(&pipe->current_tokens, free_token);
	exit(1);
}

void	handle_parent_process_pipe(int fd[2], int *prev_pipe)
{
	close(fd[1]);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	*prev_pipe = fd[0];
}

void	initialise_pipe(t_pipe *pipe, t_prompt *prompt)
{
	pipe->current_tokens = prompt->token_lst;
	pipe->list1 = NULL;
	pipe->list2 = NULL;
	pipe->pipe_count = count_pipes(prompt->token_lst);
	pipe->prev_pipe = -1;
	pipe->i = 0;
}

void	piping(t_prompt *prompt)
{
	t_pipe	pipe;

	initialise_pipe(&pipe, prompt);
	while (pipe.i <= pipe.pipe_count)
	{
		split_tokens(pipe.current_tokens, &pipe.list1, &pipe.list2, TOKEN_PIPE);
		pipe.current_tokens = pipe.list2;
		create_pipes(pipe.i, pipe.pipe_count, pipe.fd);
		pipe.pid = create_child_process();
		if (pipe.pid == 0)
			handle_child_process_pipe(&pipe, prompt->env_copy);
		else
			handle_parent_process_pipe(pipe.fd, &pipe.prev_pipe);
		pipe.i++;
		lst_cleanup(&pipe.list1, free_token);
	}
	if (pipe.prev_pipe != -1)
		close(pipe.prev_pipe);
	lst_cleanup(&pipe.list2, free_token);
	wait_for_children(pipe.pipe_count + 1);
}
