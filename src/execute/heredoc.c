/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:14:03 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/31 11:59:37 by yhusieva         ###   ########.fr       */
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
	int		fd;
	char	*tmp;

	tmp = "/tmp/filename_temp";
	if (!tmp || heredoc_redirection(list2->value, tmp) == -1)
		return (unlink(tmp), -1);
	if (count_heredocs(list2))
		return (0);
	fd = open(tmp, O_RDONLY);
	if (fd == -1)
		return (perror("Failed to open file"), unlink(tmp), -1);
	restore_stdinout(&fd, NULL);
	return (unlink(tmp), 0);
}
