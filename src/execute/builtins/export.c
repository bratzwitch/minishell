#include "../../include/minishell.h"

/* Using ***env allows us to reallocate and replace the pointer to the env array itself. (e.g. *env = new_env;)
    This is necessary if we expand the environment list to add a new variable and want
        the change to persist outside the function.
    However, if you're only appending to the existing env without replacing
        it entirely, **env is sufficient. */

int find_var(char *name, char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (strncmp(env[i], name, strlen(name)) == 0)
        {
            printf("found var at %d\n", i);
            return (i);
        }
        i++;
    }
    return (-1);
}

void add_new_var(char **env, char *new_var, int index)
{
    int i = 0;

    if (index >= 0)
        env[index] = new_var;
    else
    {
        while (env[i])
            i++;
        env[i] = new_var;
        env[i + 1] = NULL;
    }
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

char *ft_setenv(char *name, char **env, char *new_var)
{
    int i;
    char *cut_name;

    if (name == NULL || ft_strchr(name, '=') == NULL)
        return (NULL);
    new_var = ft_strdup(name);
    if (!new_var)
        return (NULL);
    cut_name = get_var_name(name);
    if (!cut_name)
        return (NULL);
    printf("cut: %s\n", cut_name);
    i = find_var(cut_name, env);
    free(cut_name);
    add_new_var(env, new_var, i);
    return (new_var);
}

int handle_export(t_prompt *prompt, t_token *tokens, char **env)
{
    t_token *tmp = tokens;
    char *vars;

    vars = NULL;
    while (tmp)
    {
        vars = ft_setenv(tmp->value, env, vars);
        tmp = tmp->next;
    }
    if (!vars)
    {
        printf("minishell: export: error\n");
        return (1);
    }
    if (prompt)
        prompt->exported_vars = vars;
    return (0);
}

// error example: bash: export: `C1+LOL': not a valid identifier