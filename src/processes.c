#include "../include/minishell.h"

// if you want to access the value of the token here's the syntax: (*prompt->token_lst)->value
void handle_child_process(t_prompt *prompt, char **env) // uses fd[1] - writing end - close fd[0]
{
	execute(prompt->token_lst, prompt->path, env);
	printf("No food today: %s\n", strerror(errno));
	cleanup(prompt); // idk how it'll help but let it be
	exit(1);
}

void handle_parent_process(pid_t id, int *exit_status, t_prompt *prompt) // uses fd[0] - reading end - close fd[1]
{
	add_history(prompt->input);
	waitpid(id, exit_status, 0);
	if (WIFEXITED(*exit_status))
	{
		received_sig = WEXITSTATUS(*exit_status);
		// printf("Process exited with status %d\n", WEXITSTATUS(*exit_status));
	}
	else if (WIFSIGNALED(*exit_status))
	{
		received_sig = 128 + WTERMSIG(*exit_status);
		// printf("Process terminated by signal %d\n", 128 + WTERMSIG(*exit_status));
	}
	else if (WIFSTOPPED(*exit_status))
	{
		received_sig = WSTOPSIG(*exit_status);
		// printf("stopped by signal %d\n", WSTOPSIG(*exit_status));
	}
}
	// If both the read and write ends are open in both processes,
	// 	it can lead to deadlocks where both processes are waiting
	// 	for each other to perform an action.