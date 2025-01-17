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

int	handle_exit(t_prompt *prompt)
{
	printf("exit\n");
	if (prompt->token_lst == NULL)
	{
		printf("Error: token list is NULL\n");
		return (1);
	}
	if (count_tokens(prompt->token_lst) > 2)
	{
		received_sig = 1;
		printf("exit: too many arguments\n");
	}
	if (prompt->token_lst->next)
	{
		if (prompt->token_lst->next && ft_is_num(prompt->token_lst->next->value))
		    received_sig = ft_atoi(prompt->token_lst->next->value);
		else if (!ft_is_num(prompt->token_lst->next->value))
		{
			received_sig = 2;
			printf("exit: numeric argument required\n");
		}
	}
    ft_free(prompt->env_copy);
	lst_cleanup(&prompt->token_lst, free_token);
	cleanup(prompt);
	exit(received_sig);
}
