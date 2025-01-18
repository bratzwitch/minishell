#include "../include/minishell.h"

void	handle_child_process_pipe(t_pipe *pipe, char **env)
{
	struct sigaction sa_default;

    sigemptyset(&sa_default.sa_mask);
    sa_default.sa_flags = 0;
    sa_default.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sa_default, NULL);
	if (ft_is_special_token(pipe->list2) == TOKEN_HEREDOC)
	{
		if (heredoc_redirection(pipe->list2->next->value) == -1)
		{
			printf("Heredoc redirection failed.\n");
			return ;
		}
	}
	if (pipe->prev_pipe != -1)
		restore_stdinout(&pipe->prev_pipe, NULL);
	if (pipe->i < pipe->pipe_count)
		restore_stdinout(NULL, &pipe->fd[1]);
	else
		close(pipe->fd[1]);
	close(pipe->fd[0]);
	if(validator(pipe->list1->value))
		execute(pipe->list1, NULL, env);
	else
	{
		ft_free(env);
		lst_cleanup(&pipe->list1, free_token); // validate the input in the "piping" ft before even forking a child.
		lst_cleanup(&pipe->current_tokens, free_token);
	}
	exit(1);
}

void handle_parent_process_pipe(int fd[2], int *prev_pipe)
{
	struct sigaction sa_ignore, sa_orig;

    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sa_ignore.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa_ignore, &sa_orig);
	close(fd[1]);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	*prev_pipe = fd[0];
}

void	piping(t_prompt *prompt)
{
	t_pipe	pipe;

	pipe.current_tokens = prompt->token_lst;
	pipe.list1 = NULL;
	pipe.list2 = NULL; // write a ft "initialise_pipe" for prettiness
	pipe.pipe_count = count_pipes(prompt->token_lst);
	pipe.prev_pipe = -1;
	pipe.i = 0;
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
	}
	if (pipe.prev_pipe != -1)
		close(pipe.prev_pipe);
	lst_cleanup(&pipe.list1,free_token);
	lst_cleanup(&pipe.list2,free_token);
	lst_cleanup(&pipe.current_tokens,free_token);
	wait_for_children(pipe.pipe_count + 1);
}
