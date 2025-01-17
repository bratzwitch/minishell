#include "../include/minishell.h"

pid_t	create_child_process(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}

// if you want to access the value of the token here's the syntax: (*prompt->token_lst)->value
void handle_child_process(t_prompt *prompt, char **env) // uses fd[1] - writing end - close fd[0]
{
	struct sigaction sa_default;

    sigemptyset(&sa_default.sa_mask);
    sa_default.sa_flags = 0;
    sa_default.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sa_default, NULL);

	execute(prompt->token_lst, prompt->path, env);
	printf("No food today: %s\n", strerror(errno));
	cleanup(prompt); // idk how it'll help but let it be
	exit(1);
}

void handle_parent_process(pid_t id, int *exit_status, t_prompt *prompt) // uses fd[0] - reading end - close fd[1]
{
	struct sigaction sa_ignore, sa_orig;

    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sa_ignore.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa_ignore, &sa_orig);

	add_history(prompt->input);
	waitpid(id, exit_status, 0);
	sigaction(SIGINT, &sa_orig, NULL);
	if (WIFEXITED(*exit_status))
		received_sig = WEXITSTATUS(*exit_status);
	else if (WIFSIGNALED(*exit_status))
		received_sig = 128 + WTERMSIG(*exit_status);
	else if (WIFSTOPPED(*exit_status))
		received_sig = WSTOPSIG(*exit_status);
	if (WIFSIGNALED(*exit_status) && WTERMSIG(*exit_status) == SIGINT)
    {
        write(STDOUT_FILENO, "\n", 1);
    }
}
	// If both the read and write ends are open in both processes,
	// 	it can lead to deadlocks where both processes are waiting
	// 	for each other to perform an action.