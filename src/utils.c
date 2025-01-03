#include "../include/minishell.h"

void	ft_free(char **values)
{
	int	i;

	i = 0;
	while (values[i])
	{
		free(values[i]);
		i++;
	}
	free(values);
}

void	lst_cleanup(t_token **head, void (*del)(t_token *))
{
	t_token	*token;
	t_token	*next;

	if (head == NULL || del == NULL)
		return ;
	token = *head;
	while (token != NULL)
	{
		next = token->next;
		del(token); // it's the same as free_token(token);
		token = next;
	}
	free(head);
}

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
