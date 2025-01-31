/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:51:35 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/31 11:02:55 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void lst_add_back(t_token **lst, t_token *new)
{
	t_token *last;

	if (!*lst)
	{
		*lst = new;
		return;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void split_tokens(t_token *head, t_token **list1, t_token **list2,
				  enum e_token_type TOKEN_TYPE)
{
	t_token *current;
	t_token *prev;

	current = head;
	prev = NULL;
	*list1 = head;
	*list2 = NULL;
	if (TOKEN_TYPE == 0)
		return;
	while (current)
	{
		if (current->type == TOKEN_TYPE)
		{
			*list2 = current->next;
			if (prev)
				prev->next = NULL;
			if (current->type == TOKEN_PIPE)
				free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

void split_free(t_token **head_ref, t_token **list1, t_token **list2, enum e_token_type TOKEN_TYPE)
{
	t_token *current;
	t_token *prev;
	t_token *redir;

	current = *head_ref;
	prev = NULL;
	*list1 = *head_ref;
	*list2 = NULL;
	if (TOKEN_TYPE == 0)
		return;
	while (current)
	{
		if (current->type == TOKEN_TYPE)
		{
			redir = current;
			*list2 = redir;
			if (!prev)
			{  
				*list1 = current->next->next;
				*head_ref = *list1;
			}
			else
				prev->next = current->next->next;
			redir->next->next = NULL;
			return;
		}
		prev = current;
		current = current->next;
	}
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
