/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:47:52 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/19 10:59:37 by yhusieva         ###   ########.fr       */
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
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	if (token_lst->next && !ft_is_num(token_lst->next->value))
	{
		ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
		return (2);
	}
	return (0);
}

static int	get_exit_status(t_token *token_lst)
{
	int result;
	
	if (token_lst->next && ft_is_num(token_lst->next->value))
	{
		result = ft_atoi(token_lst->next->value);
		if (result < 0)
            result = 256 + (result % 256);
        else if (result > 255)
            result = result % 256;
		return (result);
	}
	return (0);
}

int	handle_exit(t_prompt *prompt)
{
	int	validation_status;

	if (!prompt)
		exit(0);
	validation_status = validate_exit_arguments(prompt->token_lst);
	if (validation_status > 0)
	{
		g_received_sig = validation_status;
		exit(g_received_sig);
	}
	g_received_sig = get_exit_status(prompt->token_lst);
	ft_free(prompt->env_copy);
	lst_cleanup(&prompt->token_lst, free_token);
	restore_stdinout(&prompt->fdin_copy, &prompt->fdout_copy);
	printf("exit\n");
	exit(g_received_sig);
}
