#include "../../../include/minishell.h"

int find_var(char *name, char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (strncmp(env[i], name, strlen(name)) == 0)
            return (i);
        i++;
    }
    return (-1);
}

int ft_unsetenv(char *name, char **env)
{
    int i;

    if (!name || !*name || strchr(name, '=') != NULL)
    {
        fprintf(stderr, "unsetenv: invalid variable name\n");
        return (-1);
    }
    if ((i = find_var(name, env)) < 0)
        return (1);
    free(env[i]);
    while (env[i])
    {
        env[i] = env[i + 1];
        i++;
    }
    return (0);
}

int handle_unset(t_token *tokens, char **env)
{
    t_token *tmp = tokens;
    (void)env;

    while (tmp && tmp->next)
    {
        if (ft_unsetenv(tmp->next->value, env) != 0)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}
