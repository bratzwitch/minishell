#include "../../include/minishell.h"

/* Using ***env allows us to reallocate and replace the pointer to the env array itself. (e.g. *env = new_env;)
    This is necessary if we expand the environment list to add a new variable and want
        the change to persist outside the function.
    However, if you're only appending to the existing env without replacing
        it entirely, **env is sufficient. */

void add_new_var(char **env, char *new_var)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    env[i] = new_var;
    env[i + 1] = NULL;
}

char *ft_setenv(char *name, char **env, char *new_var)
{
    if (name == NULL || ft_strchr(name, '=') == NULL)
        return (NULL);
    new_var = ft_strdup(name);
    if (!new_var)
        return (NULL);
    add_new_var(env, new_var);
    return (new_var);
}

int handle_export(t_prompt *prompt, t_token *tokens, char **env)
{
    t_token *tmp = tokens;
    char *vars;

    vars = NULL;
    while (tmp && tmp->next)
    {
        vars = ft_setenv(tmp->next->value, env, vars);
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