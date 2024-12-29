#include "../include/minishell.h"

pid_t create_child_process(void)
{
	pid_t id = fork();
	if (id == -1)
		printf("No fork today: %s\n", strerror(errno));
	return (id);
}

void lst_print(t_prompt *prompt) // delete after finish testing
{
	t_token *current = *(prompt->token_lst);
	
	while (current != NULL)
	{
		printf("lst: Token Type: %d, Token Value: %s\n", current->type, current->value);
		current = current->next;
	}
}

void handle_child_process(t_prompt *prompt, char **env)
{
	prompt->token_lst = lexer(prompt->input);
	// if you want to access the value of the token here's the syntax: (*prompt->token_lst)->value

	lst_print(prompt); // tests

	// SPACE FOR PARSING I GUESS

	lst_cleanup(prompt->token_lst, free_token);
	add_history(prompt->input);
	(void)env;
	// handle_input(prompt, env); // commented temporarily while testing tokens
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
