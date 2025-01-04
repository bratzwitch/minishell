#include "../include/minishell.h"

pid_t create_child_process(void)
{
	pid_t id;

	id = fork();
	if (id == -1)
		printf("No fork today: %s\n", strerror(errno));
	return (id);
}

void lst_print(t_token *token_lst) // delete after finish testing
{
	t_token *current = token_lst;

	while (current != NULL)
	{
		printf("lst: Token Type: %d, Token Value: %s\n", current->type,
			   current->value);
		current = current->next;
	}
}

void cleanup_and_exit(t_prompt *prompt, int exit_code)
{
	free(prompt->input);
	lst_cleanup(&prompt->token_lst, free_token);
	exit(exit_code);
}

int count_pipes(t_token *token_lst)
{
	t_token *temp;
	int pipes;

	pipes = 0;
	temp = token_lst;
	while (temp != NULL)
	{
		if (temp->type == TOKEN_PIPE)
		{
			pipes += 1;
			printf("pipe counted %d\n", pipes);
		}
		temp = temp->next; // we had "temp++;" and it does not iterate the list
	}
	return (pipes);
}

void handle_child_process(t_prompt *prompt, char **env)
{
	char *args[] = {NULL};
	int pipes;

	prompt->token_lst = lexer(prompt->input);
	lst_print(prompt->token_lst); // tests

	pipes = count_pipes(prompt->token_lst);
	// if (pipes >= 1)
	// 	piping(prompt->token_lst, pipes, *env);
	
	// if you want to access the value of the token here's the syntax: (*prompt->token_lst)->value
	
	if (prompt->input[0] == '\0')
		cleanup_and_exit(prompt, 0);
	else if (handle_builtins(prompt, prompt->token_lst, args, env) != 0)
	{
		printf("Buildins?? : %s\n", strerror(errno));
		cleanup_and_exit(prompt, 1);
	}
	cleanup_and_exit(prompt, 0);
}

bool is_history(char *input)
{
	char *trimmed_input = ft_strtrim(input, " \t\n\v\f\r");

	if (trimmed_input[0] == '\0')
	{
		free(trimmed_input);
		return (false);
	}
	free(trimmed_input);
	return (true);
}

void handle_parent_process(pid_t id, int *exit_status, t_prompt *prompt)
{
	if (is_history(prompt->input))
		add_history(prompt->input);
	waitpid(id, exit_status, 0);
	if (WIFEXITED(*exit_status))
		printf("Process exited with status %d\n", WEXITSTATUS(*exit_status));
	else if (WIFSIGNALED(*exit_status))
		printf("Process terminated by signal %d\n", 128 + WTERMSIG(*exit_status));
	// printf("ZZzzZzz... End of the process id: %d\n", id);
}
