#include "../include/minishell.h"

pid_t create_child_process(void)
{
	pid_t id;

	id = fork();
	if (id == -1)
		printf("No fork today: %s\n", strerror(errno));
	return (id);
}

void handle_child_process(t_prompt *prompt, char **env) // uses fd[1] - writing end - close fd[0]
{
	int pipes;

	// prompt->token_lst = lexer(prompt->input);
	lst_print(prompt->token_lst); // tests

	pipes = count_pipes(prompt->token_lst);
	// if (pipes >= 1)
	// 	piping(prompt->token_lst, pipes, *env);

	// if you want to access the value of the token here's the syntax: (*prompt->token_lst)->value

	if (prompt->input[0] == '\0')
		cleanup_and_exit(prompt, 0);
	else if (execute(prompt->token_lst->value, env) != 0)
	{
		printf("Buildins?? : %s\n", strerror(errno));
		cleanup_and_exit(prompt, 1);
	}
	cleanup_and_exit(prompt, 0);
}

void handle_parent_process(pid_t id, int *exit_status, t_prompt *prompt) // uses fd[0] - reading end - close fd[1]
{
	if (is_history(prompt->input))
		add_history(prompt->input);
	waitpid(id, exit_status, 0);
	if (WIFEXITED(*exit_status))
		printf("Process exited with status %d\n", WEXITSTATUS(*exit_status));
	else if (WIFSIGNALED(*exit_status))
		printf("Process terminated by signal %d\n", 128 + WTERMSIG(*exit_status));
}

// If both the read and write ends are open in both processes,
// 	it can lead to deadlocks where both processes are waiting
// 	for each other to perform an action.