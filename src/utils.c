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

void cleanup_and_exit(t_prompt *prompt, int exit_code)
{
	free(prompt->input);
	lst_cleanup(&prompt->token_lst, free_token);
	exit(exit_code);
}

bool is_history(char *input)
{
	char *trimmed_input = ft_strtrim(input, " \t\n\v\f\r");

	if (trimmed_input[0] == '\0')
	{
		free(trimmed_input);
		return (false);
	}
	free(trimmed_input);
	return (true);
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
	*head = NULL;
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
