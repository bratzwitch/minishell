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
        perror("Error pwd.");
        return (2);
    }
    printf("%s\n", path);
    free(path);
    return (0);
}

int handle_exit(t_prompt *prompt)
{
    if (prompt->token_lst->next)
    {
        received_sig = ft_atoi(prompt->token_lst->next->value);
    }
    printf("exit\n");
    cleanup(prompt);
    exit(received_sig);
}
