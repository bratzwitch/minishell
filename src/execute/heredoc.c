#include "../../include/minishell.h"

int	heredoc_redirection(const char *delimiter)
{
	char	*line;
	int		pipe_fd[2];
	pid_t	pid;
	int		fd;

	fd = open("/tmp/.sh-thd-865008963", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC,
			0600);
	if (fd == -1)
	{
		perror("Failed to open file for heredoc");
		return (-1);
	}
	if (pipe(pipe_fd) == -1)
	{
		perror("no pipe for heredoc");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		while (1)
		{
			line = readline("heredoc> ");
			if (line == NULL || strcmp(line, delimiter) == 0)
			{
				free(line);
				break ;
			}
			write(pipe_fd[1], line, strlen(line));
			write(pipe_fd[1], "\n", 1);
			free(line);
		}
		close(fd);
		close(pipe_fd[1]);
		exit(0);
	}
	else
	{
		close(pipe_fd[1]);
		unlink("/tmp/.sh-thd-865008963");
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		{
			perror("No redir for heredoc");
			close(pipe_fd[0]);
			return (-1);
		}
		close(pipe_fd[0]);
		waitpid(pid, NULL, 0);
	}
	return (0);
}
