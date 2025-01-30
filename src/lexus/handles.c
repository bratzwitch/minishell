/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:09:32 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/30 12:32:24 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_quotes(char **current, char *final_str)
{
	char	quote;

	quote = *(*current);
	if (quote == '\'')
		final_str = handle_single_quotes(current, final_str);
	else if (quote == '\"')
		final_str = handle_double_quote(current, final_str);
	return (final_str);
}

char	*handle_regular_characters(char **current, char *final_str)
{
	char	*start;

	start = *current;
	while (*(*current) && !ft_isspace(*(*current))
		&& !ft_is_special_character(*current) && !ft_is_quotes(*current))
		(*current)++;
	return (append_to_final_str(final_str, start, *current - start));
}

char	*process_current_char(char **current, char *final_str)
{
	if (ft_is_quotes(*current))
		final_str = handle_quotes(current, final_str);
	else
		final_str = handle_regular_characters(current, final_str);
	return (final_str);
}

char	*process_whitespace(char *current)
{
	while (*current && ft_isspace(*current))
		current++;
	return (current);
}
