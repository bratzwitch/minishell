/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:14:06 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 13:14:06 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	input_redirection(const char *file_name)
{
	int	fd_in;

	fd_in = open(file_name, O_RDONLY);
	if (fd_in == -1)
	{
		perror("Error opening file.");
		return (-1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("Error redirecting input.");
		close(fd_in);
		return (-1);
	}
	close(fd_in);
	return (0);
}

int	redirect_stdout(const char *file_name, int flags)
{
	int	fd_out;

	fd_out = open(file_name, flags, 0644);
	if (fd_out == -1)
	{
		perror("Error opening file for output redirection");
		return (-1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output");
		close(fd_out);
		return (-1);
	}
	close(fd_out);
	return (0);
}

int	output_redirection(const char *file_name)
{
	int	flags;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	return (redirect_stdout(file_name, flags));
}

int	append_redirection(const char *file_name)
{
	int	flags;

	flags = O_WRONLY | O_CREAT | O_APPEND;
	return (redirect_stdout(file_name, flags));
}
