/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:59:31 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/30 11:02:02 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void sig_handler(int signum)
{
	g_received_sig = 128 + signum;
	if (!no_nl(3))
		write(STDERR_FILENO, "\n", 1);
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void setup_handlers(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sig_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		write(STDERR_FILENO, "Error: sigaction SIGINT\n", 25);
		exit(1);
	}
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		write(STDERR_FILENO, "Error: sigaction SIGQUIT\n", 26);
		exit(1);
	}
}
