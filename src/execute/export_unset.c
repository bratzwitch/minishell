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
    {
        printf("minishell: export: '%s': not a valid identifier\n", name);
        return (NULL);
    }
    new_var = ft_strdup(name);
    if (!new_var)
        return (NULL);
    add_new_var(env, new_var);
    return (new_var);
}

int handle_export(t_prompt *prompt, char **env)
{
    t_token *tmp = prompt->token_lst;

    (void)tmp;
    prompt->exported_vars = ft_setenv("LOL=C1", env, prompt->exported_vars);
    if (prompt->exported_vars != NULL)
    {
        return (0);
    }
    else
    {
        perror("setenv");
        return (1);
    }
}

// error example: bash: export: `C1+LOL': not a valid identifier