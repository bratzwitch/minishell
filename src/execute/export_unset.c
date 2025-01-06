#include "../../include/minishell.h"

// UTILS

int validate_input(const char *name, const char *value)
{
    if (name == NULL || value == NULL || strchr(name, '=') != NULL)
    {
        fprintf(stderr, "ft_setenv: Invalid name or value\n");
        return (-1);
    }
    return (0);
}

void format_env_var(char *buffer, const char *name, const char *value)
{
    strcpy(buffer, name);
    strcat(buffer, "=");
    strcat(buffer, value);
}

char *create_new_var(const char *name, const char *value)
{
    char *new_var;

    new_var = malloc(ft_strlen(name) + ft_strlen(value) + 2);
    if (!new_var)
    {
        perror("malloc");
        return (NULL);
    }
    format_env_var(new_var, name, value);
    printf("%s\n", new_var);
    return (new_var);
}

int find_existing_var(char **env, const char *name, size_t name_len)
{
    int i = 0;

    while (env[i])
    {
        if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
            return (i);
        i++;
    }
    return (-1);
}

int update_existing_var(char **env, int index, char *new_var, int overwrite)
{
    if (!overwrite)
    {
        free(new_var);
        return 0;
    }
    env[index] = new_var;
    free(env[index]);
    return (0);
}

// ACTION

int add_new_var(char ***env, char *new_var)
{
    char **new_env;
    int count;
    int i;

    count = 0;
    while ((*env)[count])
        count++;
    new_env = malloc((count + 2) * sizeof(char *));
    if (!new_env)
    {
        perror("malloc");
        free(new_var);
        return (-1);
    }
    i = 0;
    while (i < count)
    {
        new_env[i] = (*env)[i];
        i++;
    }
    new_env[count] = new_var;
    new_env[count + 1] = NULL;
    *env = new_env;
    free(*env);
    return (0);
}

int ft_setenv(const char *name, const char *value, int overwrite, char **env)
{
    size_t name_len;
    int existing_index;
    char *new_var;

    if (validate_input(name, value) < 0)
        return (-1);
    new_var = create_new_var(name, value);
    if (!new_var)
        return (-1);
    name_len = ft_strlen(name);
    existing_index = find_existing_var(env, name, name_len);
    if (existing_index >= 0)
        return (update_existing_var(env, existing_index, new_var, overwrite));
    return (add_new_var(&env, new_var));
}

int handle_export(t_token *token, char **env)
{
    t_token *tmp = token;

    (void)tmp;
    if (ft_setenv("LOL", "C1", 1, env) == 0)
    {
        handle_env(env);
        return (0);
    }
    else
    {
        perror("setenv");
        return (1);
    }
}
