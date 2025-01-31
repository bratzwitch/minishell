/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:51:35 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/31 12:11:57 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lst_add_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	split_tokens(t_token *head, t_token **list1, t_token **list2,
		enum e_token_type TOKEN_TYPE)
{
	t_token	*current;
	t_token	*prev;

	current = head;
	prev = NULL;
	*list1 = head;
	*list2 = NULL;
	if (TOKEN_TYPE == 0)
		return ;
	while (current)
	{
		if (current->type == TOKEN_TYPE)
		{
			*list2 = current->next;
			if (prev)
				prev->next = NULL;
			if (current->type == TOKEN_PIPE)
				free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	split_free(t_token **head, t_token **list1, t_token **list2,
		enum e_token_type type)
{
	t_token	*cur;
	t_token	*prev;

	cur = *head;
	prev = NULL;
	*list1 = *head;
	*list2 = NULL;
	if (!type)
		return ;
	while (cur && cur->type != type)
	{
		prev = cur;
		cur = cur->next;
	}
	if (!cur)
		return ;
	*list2 = cur;
	if (!prev)
		*head = cur->next->next;
	else
		prev->next = cur->next->next;
	cur->next->next = NULL;
}

int	count_tokens(t_token *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**lst_to_arr(t_token *tokens)
{
	t_token	*tmp;
	char	**args;
	int		count;
	int		i;

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
