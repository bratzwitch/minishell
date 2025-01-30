/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:53:23 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/30 13:28:32 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**copy_env(char **env)
{
	int		i;
	char	**copy;

	i = 0;
	while (env[i])
		i++;
	copy = malloc((i + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	ft_free(char **values)
{
	int	i;

	i = 0;
	if (!values)
		return ;
	while (values[i])
	{
		free(values[i]);
		i++;
	}
	free(values);
}

void	free_token(t_token *t)
{
	if (t)
	{
		if (t->type == TOKEN_ARGUMENT)
			free(t->value);
		free(t);
	}
}

void	lst_cleanup(t_token **head, void (*del)(t_token *))
{
	t_token	*token;
	t_token	*next;

	token = *head;
	while (token != NULL)
	{
		next = token->next;
		del(token);
		token = next;
	}
	*head = NULL;
}

void	cleanup(t_prompt *prompt)
{
	rl_clear_history();
	if (!prompt)
		return ;
	if (prompt->input)
    	free(prompt->input);
	if (prompt->path)
    	free(prompt->path);
	lst_cleanup(&prompt->token_lst, free_token);
}
