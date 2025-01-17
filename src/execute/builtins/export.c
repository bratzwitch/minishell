#include "../../../include/minishell.h"

/* Using ***env allows us to reallocate and replace the pointer to the env array itself. (e.g. *env = new_env;)
    This is necessary if we expand the environment list to add a new variable and want
        the change to persist outside the function.
    However, if you're only appending to the existing env without replacing
        it entirely, **env is sufficient. */

    /* Summary of Pointer Levels
char ***env: Used when the pointer itself may need to be updated.
char **env: Used when only the contents of the pointer are modified, not the pointer itself.

Think of it like this:
char ***env: A manager who can hire a new assistant (assign a new address).
char **env: An assistant who only works with files on their desk (data at the address). */

int ft_is_valid_identifier(char *name)
{
    if (!ft_isalpha(*name) && *name != '_')
        return (true);
    name++;
    while (*name && *name != '=')
    {
        if (!(ft_isalpha(*name)) && *name != '_')
            return (true);
        name++;
    }
    return (false);
}

char *get_var_name(const char *name)
{
    char *equal_sign;
    size_t len;

    equal_sign = strchr(name, '=');
    if (!equal_sign)
        return (NULL);
    len = equal_sign - name;
    return (strndup(name, len));
}


char **expand_env(char **env, int new_size)
{
    char **new_env;
    int i = 0;

    new_env = malloc((new_size + 1) * sizeof(char *));
    if (!new_env)
        return (NULL);
    while (env && env[i])
    {
        new_env[i] = env[i];
        i++;
    }
    new_env[i] = NULL;
    free(env);
    return (new_env);
}

void add_new_var(char ***env, char *new_var, int index)
{
    int i = 0;
    int size = 0;

    while (*env && (*env)[size])
        size++;
    if (index >= 0)
    {
        free((*env)[index]);
        (*env)[index] = new_var;
    }
    else
    {
        if (i >= size)
        {
            *env = expand_env(*env, size + 1);
            if (!*env)
            {
                perror("Failed to expand env");
                free(new_var);
                return;
            }
        }
        while ((*env)[i])
            i++;
        (*env)[i] = new_var;
        (*env)[i + 1] = NULL;
    }
}

char *ft_setenv(char *name, char **env)
{
    int i;
    char *new_var;
    char *cut_name;

    if (!name || !ft_strchr(name, '='))
        return (NULL);
    new_var = ft_strdup(name);
    if (!new_var)
        return (NULL);
    cut_name = get_var_name(name);
    if (!cut_name)
        return (NULL);
    i = find_var(cut_name, env);
    free(cut_name);
    add_new_var(&env, new_var, i);
    return (new_var);
}

int handle_export(t_token *tokens, char **env)
{
    t_token *tmp = tokens;

    while (tmp)
    {
        if (ft_is_valid_identifier(tmp->value))
            return (1);
        ft_setenv(tmp->value, env);
        tmp = tmp->next;
    }
    return (0);
}

// error example: bash: export: `C1+LOL': not a valid identifier