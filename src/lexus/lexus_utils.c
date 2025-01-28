/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:39:25 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/28 15:00:56 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	ft_isspace(const char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

bool	ft_is_special_character(const char *current)
{
	return (*current == '<' || *current == '>' || *current == '|'
		|| ft_strncmp(current, "<<", 2) == 0 || ft_strncmp(current, ">>", 2) == 0);
}

bool	ft_is_quotes(const char *current)
{
	return (*current == '\'' || *current == '\"');
}

int	ft_quotes(char *str, int size)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (str[i] && i < size)
	{
		if (trigger == 0 && str[i] == '\"')
			trigger = 2;
		else if (trigger == 0 && str[i] == '\'')
			trigger = 1;
		else if (trigger == 2 && str[i] == '\"')
			trigger = 0;
		else if (trigger == 1 && str[i] == '\'')
			trigger = 0;
		i++;
	}
	return (trigger);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}
