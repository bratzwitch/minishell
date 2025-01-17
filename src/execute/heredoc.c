#include "../../include/minishell.h"
/* What Does Heredoc Do?
1. A heredoc reads the input provided between a delimiter (e.g., <<END)
and passes it as standard input (stdin) to a command.

2. Instead of reading input from a file or line by line interactively,
heredoc enables you to type out all the input inline. */

void child_heredoc_process(int write_fd, const char *delimiter)
{
	char *line;

	// close(STDIN_FILENO);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || !strcmp(line, delimiter))
		{
			free(line);
			break;
		}
		ft_putendl_fd(line, write_fd);
		free(line);
	}
	close(write_fd);
	exit(0);
}

int heredoc_redirection(const char *delimiter)
{
	int pipe_fd[2];
	pid_t pid;

	if (create_pipe(pipe_fd) == -1)
		return (-1);
	pid = create_child_process();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		child_heredoc_process(pipe_fd[1], delimiter);
	}
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			perror("Failed to redirect stdin for heredoc");
			close(pipe_fd[0]);
			return (-1);
		}
		close(pipe_fd[0]);
	}
	return (0);
}
