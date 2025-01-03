#include "../include/minishell.h"

pid_t create_child_process(void)
{
	pid_t id = fork();
	if (id == -1)
		printf("No fork today: %s\n", strerror(errno));
	return (id);
}

void lst_print(t_token **token_lst) // delete after finish testing
{
	t_token *current = *(token_lst);
	
	while (current != NULL)
	{
		printf("lst: Token Type: %d, Token Value: %s\n", current->type, current->value);
		current = current->next;
	}
}

void handle_child_process(t_prompt *prompt, char **env)
{
	char *args[] = {NULL};

	prompt->token_lst = lexer(prompt->input);
	// if you want to access the value of the token here's the syntax: (*prompt->token_lst)->value
	lst_print(prompt->token_lst); // tests

	// SPACE FOR PARSING I GUESS
	if (prompt->input[0] == '\0')
	{
		free(prompt->input);
		free(prompt->token_lst);
		exit(0) ;
	}
	else if (handle_builtins(prompt, prompt->token_lst, args, env) != 0)
	{
		free(prompt->input);
		printf("Buildins?? : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	add_history(prompt->input);
	lst_cleanup(prompt->token_lst, free_token);
	free(prompt->input);
	exit(EXIT_SUCCESS); // exit the child process
}

void handle_parent_process(pid_t id, int *exit_status, t_prompt *prompt)
{
	add_history(prompt->input);
	waitpid(id, exit_status, 0);
	if (WIFEXITED(*exit_status))
		printf("Process exited with status %d\n", WEXITSTATUS(*exit_status));
	else if (WIFSIGNALED(*exit_status))
		printf("Process terminated by signal %d\n", 128 + WTERMSIG(*exit_status));
	// printf("ZZzzZzz... End of the process id: %d\n", id);
}
