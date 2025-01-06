#include "../include/minishell.h"

void ft_free(char **values)
{
	int i;

	i = 0;
	while (values[i])
	{
		free(values[i]);
		i++;
	}
	free(values);
}

void free_token(t_token *t)
{
	if (t->type == TOKEN_ARGUMENT)
		free(t->value);
	free(t);
}

void lst_cleanup(t_token **head, void (*del)(t_token *))
{
	t_token *token;
	t_token *next;

	token = *head;
	while (token != NULL)
	{
		next = token->next;
		del(token); // it's the same as free_token(token);
		token = next;
	}
	*head = NULL;
}

void cleanup(t_prompt *prompt)
{
	free(prompt->input);
	free(prompt->path);
	free(prompt->exported_vars);
	lst_cleanup(&prompt->token_lst, free_token);
	rl_clear_history();
}

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

void lst_print(t_token *token_lst) // delete after finish testing
{
	t_token *current = token_lst;

	while (current != NULL)
	{
		printf("lst: Token Type: %d, Token Value: %s\n", current->type,
			   current->value);
		current = current->next;
	}
}
