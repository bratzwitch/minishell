#include "../include/minishell.h"

pid_t create_child_process(void)
{
	pid_t id;

	id = fork();
	if (id == -1)
		printf("No fork today: %s\n", strerror(errno));
	return (id);
}

int count_tokens(t_token *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char **lst_to_arr(t_token *tokens)
{
	t_token *tmp;
	char **args;
	int count;
	int i;

	tmp = tokens;
	count = count_tokens(tokens);
	args = (char **)malloc((count + 1) * sizeof(char *));
	i = 0;
	while (i < count && tmp)
	{
		args[i] = tmp->value;
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void print_args(char **args)
{
	int i = 0;
	while (args[i])
	{
		printf("args: %s\n", args[i]);
		i++;
	}
}

int execute(t_prompt *prompt, char **env)
{
	char **args;

	args = lst_to_arr(prompt->token_lst);
	if (execve(prompt->path, args, env) < 0)// exits automatically and free all memory in use (spoiler not all)
		return (-1);
	return (0);
}

// if you want to access the value of the token here's the syntax: (*prompt->token_lst)->value
void handle_child_process(t_prompt *prompt, char **env) // uses fd[1] - writing end - close fd[0]
{
	// int pipes;

	// pipes = count_pipes(prompt->token_lst);
	// if (pipes >= 1)
	// 	piping(prompt, env);

	if (execute(prompt, env) < 0)
		printf("No food today: %s\n", strerror(errno));
	cleanup(prompt); // idk how it'll help but let it be
}

void handle_parent_process(pid_t id, int *exit_status, t_prompt *prompt) // uses fd[0] - reading end - close fd[1]
{
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



