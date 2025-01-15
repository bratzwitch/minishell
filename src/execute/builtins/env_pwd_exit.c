#include "../../../include/minishell.h"

int handle_env(char **env)
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

int handle_pwd()
{
    char *path;

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

int handle_exit(t_prompt *prompt)
{
    printf("exit\n");
    if (count_tokens(prompt->token_lst) > 2)
    {
        received_sig = 1;
        printf("exit: too many arguments\n");
    }
    else if (prompt->token_lst->next && ft_is_num(prompt->token_lst->next->value))
        received_sig = ft_atoi(prompt->token_lst->next->value);
    else if (!ft_is_num(prompt->token_lst->next->value))
    {
        received_sig = 2;
        printf("exit: numeric argument required\n");
    }
    cleanup(prompt);
    exit(received_sig);
}
