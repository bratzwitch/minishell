/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:47:52 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 13:57:46 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	handle_env(char **env)
{
	if (!env)
		return (2);
	while (*env)
	{
		ft_putendl_fd(*env, 1);
		env++;
	}
	return (0);
}

int	handle_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd");
		return (2);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

static int	validate_exit_arguments(t_token *token_lst)
{
	int	token_count;

	token_count = count_tokens(token_lst);
	if (token_count > 2)
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	if (token_lst->next && !ft_is_num(token_lst->next->value))
	{
		printf("exit: numeric argument required\n");
		return (2);
	}
	return (0);
}

static int	get_exit_status(t_token *token_lst)
{
	if (token_lst->next && ft_is_num(token_lst->next->value))
		return (ft_atoi(token_lst->next->value));
	return (0);
}

int	handle_exit(t_prompt *prompt)
{
	int	validation_status;

	printf("bye\n");
	if (!prompt->token_lst)
	{
		printf("Error: token list is NULL\n");
		exit(1);
	}
	validation_status = validate_exit_arguments(prompt->token_lst);
	if (validation_status > 0)
	{
		g_received_sig = validation_status;
		if (validation_status == 1)
			return (1);
	}
	g_received_sig = get_exit_status(prompt->token_lst);
	ft_free(prompt->env_copy);
	lst_cleanup(&prompt->token_lst, free_token);
	restore_stdinout(&prompt->fdin_copy, &prompt->fdout_copy);
	exit(g_received_sig);
}
