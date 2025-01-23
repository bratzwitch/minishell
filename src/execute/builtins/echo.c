/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmoroz <vmoroz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:47:49 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/23 12:34:02 by vmoroz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	handle_echo(t_token *token)
{
	t_token	*tmp;
	bool	is_n;

	tmp = NULL;
	if (token)
		tmp = token->next;
	is_n = false;
	if (tmp && !ft_strcmp(tmp->value, "-n"))
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		is_n = true;
		tmp = tmp->next;
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->value, 1);
		if (tmp->next)
			ft_putchar_fd(' ', 1);
		tmp = tmp->next;
	}
	if (!is_n)
		ft_putchar_fd('\n', 1);
	return (0);
}
