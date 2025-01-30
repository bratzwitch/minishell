/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:14:03 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/30 13:26:16 by yhusieva         ###   ########.fr       */
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
int heredoc_redirection(const char *delimiter, const char *tmp_filename)
{
    int     tmp_fd;

    tmp_fd = open(tmp_filename, O_CREAT | O_WRONLY | O_APPEND, 0600);
    if (tmp_fd == -1)
    {
        perror("Failed to create temporary file");
        return (-1);
    }
	write_to_tmp(tmp_fd, delimiter);
    return (0);
}

int handle_heredoc(t_token *list2)
{
    int tmp_fd;
	char *tmp_filename;

    tmp_filename = generate_temp_filename();
    if (!tmp_filename)
    {
        perror("Failed to allocate memory for temporary filename");
        return (-1);
    }
    if (heredoc_redirection(list2->value, tmp_filename) == -1)
	{
		unlink(tmp_filename);
		free(tmp_filename);
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
	free(tmp_filename);
    return (0);
}
