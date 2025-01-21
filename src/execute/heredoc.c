/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:14:03 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/21 14:12:25 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_heredoc_process(int write_fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line || !strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, write_fd);
		free(line);
	}
	close(write_fd);
	exit(0);
}

char	*generate_temp_filename(void)
{
	char	*base;
	char	*filename;
	int		pid;
	int		counter;
	int		len;
	char	pid_str[10];
	char	counter_str[10];
	char	temp;
	int		i;
	int		j;

	base = "/tmp/heredoc_temp_";
	pid = getpid();
	counter = 0;
	len = ft_strlen(base);
	i = 0;
	while (pid > 0 || i == 0)
	{
		pid_str[i] = '0' + (pid % 10);
		pid /= 10;
		i++;
	}
	pid_str[i] = '\0';
	j = 0;
	while (j < i / 2)
	{
		temp = pid_str[j];
		pid_str[j] = pid_str[i - j - 1];
		pid_str[i - j - 1] = temp;
		j++;
	}
	i = 0;
	while (counter > 0 || i == 0)
	{
		counter_str[i] = '0' + (counter % 10);
		counter /= 10;
		i++;
	}
	counter_str[i] = '\0';
	j = 0;
	while (j < i / 2)
	{
		temp = counter_str[j];
		counter_str[j] = counter_str[i - j - 1];
		counter_str[i - j - 1] = temp;
		j++;
	}
	filename = malloc(len + strlen(pid_str) + strlen(counter_str) + 2);
	if (!filename)
		return (NULL);
	strcpy(filename, base);
	strcat(filename, pid_str);
	strcat(filename, "_");
	strcat(filename, counter_str);
	return (filename);
}

int	heredoc_redirection(const char *delimiter)
{
	char	*line;
	char	*tmp_filename;
	int		tmp_fd;

	tmp_filename = generate_temp_filename();
	if (!tmp_filename)
	{
		perror("Failed to allocate memory for temporary filename");
		return (-1);
	}
	tmp_fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (tmp_fd == -1)
	{
		perror("Failed to create temporary file");
		free(tmp_filename);
		return (-1);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (write(tmp_fd, line, ft_strlen(line)) == -1)
		{
			perror("no write");
			free(line);
			close(tmp_fd);
			unlink(tmp_filename);
			free(tmp_filename);
			return (-1);
		}
		write(tmp_fd, "\n", 1);
		free(line);
	}
	close(tmp_fd);
	tmp_fd = open(tmp_filename, O_RDONLY);
	if (tmp_fd == -1)
	{
		perror("Failed to reopen temporary file for reading");
		unlink(tmp_filename);
		free(tmp_filename);
		return (-1);
	}
	if (dup2(tmp_fd, STDIN_FILENO) == -1)
	{
		perror("Failed to redirect stdin for heredoc");
		close(tmp_fd);
		unlink(tmp_filename);
		free(tmp_filename);
		return (-1);
	}
	close(tmp_fd);
	unlink(tmp_filename);
	free(tmp_filename);
	return (0);
}

// two heredocs dont work. try prompt: cat <<HERE <<DOC
// the thing is in how we manage our pipes.