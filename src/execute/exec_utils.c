#include "../../include/minishell.h"

enum e_token_type ft_is_special_token(t_token *head)
{
	t_token *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_REDIRECT_OUT || tmp->type == TOKEN_HEREDOC || tmp->type == TOKEN_REDIRECT_APPEND)
			return (tmp->type);
		tmp = tmp->next;
	}
	return (0);
}

bool ft_is_num(char *str)
{
    int i = 0;

    while (str[i])
    {
        if (ft_isalpha(str[i]))
            return (false);
        i++;
    }
    return (true);
}

void concatenate_tokens(t_token **tokens, t_token *list2)
{
	t_token *next;

	while (list2)
	{
		next = list2->next;
		list2->next = NULL;
		add_token(tokens, list2);
		list2 = next;
	}
}
