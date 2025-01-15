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
	rl_clear_history();
	if (!prompt)
		return ;
	free(prompt->input);
	free(prompt->path);
	free(prompt->exported_vars);
	lst_cleanup(&prompt->token_lst, free_token);
}

int is_pipe(t_token *head)
{
	t_token *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
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
		printf("%s->", current->value);
		current = current->next;
	}
	printf("NULL\n");
}

void split_tokens(t_token *head, t_token **list1, t_token **list2, enum e_token_type TOKEN_TYPE)
{
	t_token *current = head;
	t_token *prev = NULL;

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
			current->next = NULL;
			return ;
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

void print_args(char **args)
{
	int i = 0;
	while (args[i])
	{
		printf("args: %s\n", args[i]);
		i++;
	}
}
