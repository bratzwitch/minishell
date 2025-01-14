#include "../../../include/minishell.h"

int ft_unsetenv(char *name, char **env)
{
    int i;

    if (!name || !*name || strchr(name, '=') != NULL)
    {
        fprintf(stderr, "unsetenv: invalid variable name\n");
        return (-1);
    }
    if ((i = find_var(name, env)) < 0)
        return(1);
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
        {
            fprintf(stderr, "unset: failed to unset variable: %s\n", tmp->next->value);
            return (1);
        }
        // printf("%s successfully removed.\n", tmp->next->value);
        tmp = tmp->next;
    }
    return (0);
}
