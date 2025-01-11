#include "../../../include/minishell.h"

int handle_env(char **env)
{
    if (!env)
        return (1);
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
        return (1);
    }
    printf("%s\n", path);
    free(path);
    return (0);
}

int handle_exit(t_prompt *prompt)
{
    printf("exit\n");
    cleanup(prompt);
    exit(0);
}
