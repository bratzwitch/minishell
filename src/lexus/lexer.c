/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:39:22 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/21 14:23:28 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*lexer(char *input)
{
	t_token	*token_head;
	t_token	*new_token;

	token_head = NULL;
	new_token = NULL;
	if (ft_quotes(input, ft_strlen(input)))
	{
		printf("minishell: quotes not closed. God saw you.\n");
		return (NULL);
	}
	while (*input)
	{
		while (*input && ft_isspace(*input))
			input++;
		new_token = get_next_token(&input);
		if (new_token->type == TOKEN_ERROR)
		{
			free_token(new_token);
			lst_cleanup(&token_head, free_token);
			return (NULL);
		}
		add_token(&token_head, new_token);
	}
	return (token_head);
}
