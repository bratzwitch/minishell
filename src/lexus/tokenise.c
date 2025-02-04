/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:39:34 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/31 10:39:21 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*create_token(enum e_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		ft_putendl_fd("Error creating a token", STDERR_FILENO);
		return (NULL);
	}
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

void	free_cur_and_str(char *final_str, char *current)
{
	free(final_str);
	free(current);
}

t_token	*handle_argument(char **input)
{
	char	*current;
	char	*final_str;

	current = *input;
	final_str = ft_calloc(1, 1);
	if (!final_str)
	{
		free_cur_and_str(final_str, current);
		return (NULL);
	}
	while (*current && !ft_isspace(*current))
	{
		if (*current == '$' && *(current + 1))
			final_str = dollar(&current, final_str, &current);
		final_str = process_current_char(&current, final_str);
		if (!final_str)
		{
			free_cur_and_str(final_str, current);
			return (NULL);
		}
	}
	current = process_whitespace(current);
	*input = current;
	return (create_token(TOKEN_ARGUMENT, final_str));
}

t_token	*get_next_token(char **input)
{
	char	*current;

	current = *input;
	while (*current && ft_isspace(*current))
		current++;
	if (*current == '\0')
		return (create_token(TOKEN_EOF, NULL));
	if (ft_is_special_character(current))
		return (handle_special_characters(&current, input));
	return (handle_argument(input));
}
