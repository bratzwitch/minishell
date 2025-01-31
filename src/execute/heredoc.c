/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:14:03 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/31 11:45:10 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	write_to_tmp(int write_fd, const char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc>");
		if (!line || !strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, write_fd);
		free(line);
	}
	close(write_fd);
}

int	heredoc_redirection(const char *delimiter, const char *tmp_filename)
{
	int	tmp_fd;

	tmp_fd = open(tmp_filename, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (tmp_fd == -1)
	{
		perror("Failed to create temporary file");
		return (-1);
	}
	write_to_tmp(tmp_fd, delimiter);
	return (0);
}

int	handle_heredoc(t_token *list2)
{
	int		tmp_fd;
	char	*tmp_filename;

	tmp_filename = "/tmp/filename_temp";
	if (!tmp_filename)
	{
		perror("Failed to allocate memory for temporary filename");
		return (-1);
	}
	if (heredoc_redirection(list2->value, tmp_filename) == -1)
	{
		unlink(tmp_filename);
		return (-1);
	}
	if (count_heredocs(list2) == 0)
	{
		tmp_fd = open(tmp_filename, O_RDONLY);
		if (tmp_fd == -1)
		{
			perror("Failed to reopen temporary file for reading");
			unlink(tmp_filename);
			return (-1);
		}
		restore_stdinout(&tmp_fd, NULL);
		unlink(tmp_filename);
	}
	return (0);
}
