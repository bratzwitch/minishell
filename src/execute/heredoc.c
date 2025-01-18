#include "../../include/minishell.h"

void child_heredoc_process(int write_fd, const char *delimiter)
{
	char *line;

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
		printf("Parent process handling delimiter: %s\n", delimiter);
	}
	return (0);
}

// two heredocs dont work. try prompt: cat <<HERE <<DOC
// the thing is in how we manage our pipes.