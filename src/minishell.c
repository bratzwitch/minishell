#include "../include/minishell.h"

volatile sig_atomic_t g_received_sig = 0;

char *ft_prompt(t_prompt *prompt)
{
	char *input;

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

int save_stdinout(int *fdin_copy, int *fdout_copy) // reuse these, they're very helpful. you dont have to necessarily pass both at the same time. pass like save_stdinout(NULL, &fdout); or the opposite
{
	if (fdin_copy && ((*fdin_copy = dup(STDIN_FILENO)) == -1))
	{
		perror("Error redirecting input.");
		close(*fdin_copy);
		return (-1);
	}
	if (fdout_copy && ((*fdout_copy = dup(STDOUT_FILENO)) == -1))
	{
		perror("Error redirecting input.");
		close(*fdout_copy);
		return (-1);
	}
	return (0);
}

void restore_stdinout(int *fdin_copy, int *fdout_copy) // reuse these
{
	if (fdin_copy)
	{
		if (dup2(*fdin_copy, STDIN_FILENO) == -1)
			return ;
		close(*fdin_copy);
	}
	if (fdout_copy)
	{
		if (dup2(*fdout_copy, STDOUT_FILENO) == -1)
			return ;
		close(*fdout_copy);
	}
}

void handle_single_cmd(t_prompt *prompt)
{
	pid_t pid;

	pid = 0;
	if (save_stdinout(&prompt->fdin_copy, &prompt->fdout_copy) == -1)
		return;
	g_received_sig = builtins(prompt, prompt->token_lst, prompt->env_copy);
	if (!g_received_sig || g_received_sig == 1)
	{
		restore_stdinout(&prompt->fdin_copy, &prompt->fdout_copy);
		return;
	}
	else if (!(prompt->path = validator(prompt->token_lst->value)) && !(ft_is_special_character(prompt->input)))
	{
		printf("minishell: command not found: %s\n", prompt->token_lst->value);
		restore_stdinout(&prompt->fdin_copy, &prompt->fdout_copy);
		return;
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

int main(int argc, char **argv, char **env)
{
	t_prompt prompt;

	(void)argc;
	(void)argv;

	prompt.path = NULL;
	prompt.env_copy = copy_env(env);
	setup_handlers();
	while (1)
	{
		if (!(prompt.input = ft_prompt(&prompt)))
			break;
		if(prompt.input[0] == '|')
		{
			printf("parse error near `|'\n");
			ft_free(prompt.env_copy);
			break;
		}
		if ((prompt.token_lst = lexer(prompt.input)))
		{
			if (is_pipe(prompt.token_lst))
				piping(&prompt);
			else
				handle_single_cmd(&prompt);
		}
		add_history(prompt.input);
		free(prompt.input);
		lst_cleanup(&prompt.token_lst, free_token);
	}
	return (0);
}
