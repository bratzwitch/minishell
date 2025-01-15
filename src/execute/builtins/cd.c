#include "../../../include/minishell.h"

char *format_env_var(char *name, char *value)
{
    char *result;

    result = (char *)malloc((ft_strlen(name) + ft_strlen(value) + 1) * sizeof(char));
    if (!result)
        return (NULL);
    strcpy(result, name);
    strcat(result, "=");
    strcat(result, value);
    return (result);
}

char *extract_var(char *name, char **env)
{
    char *result;
    int i;

    i = find_var(name, env);
    result = ft_strchr(env[i], '=');
    result = result + 1;
    // printf("the path is %s\n", result);
    return(result);
}

t_token *assemble_name(char *path, char **env)
{
    t_token *new_lst = NULL;
    char *new_oldpwd;
    char *new_pwd;

    new_lst = NULL;
    new_oldpwd = format_env_var("OLDPWD", extract_var("PWD", env));
    add_token(&new_lst, create_token(0, new_oldpwd));
    // printf("new OLDPWD: %s\n", new_oldpwd); // tests

    new_pwd = format_env_var("PWD", path);
    add_token(&new_lst, create_token(0, new_pwd));
    // printf("new PWD: %s\n", new_pwd); // tests
    return (new_lst);
}

int handle_cd(t_prompt *prompt, t_token *token, char **env)
{
    char *path;
    char *home;
    t_token *var_lst;

    if (!token->next)
    {
        home = getenv("HOME");
        if (!home)
        {
            perror("cd: HOME not set");
            return (1);
        }
        path = home;
    }
    else
        path = token->next->value;
    if (chdir(path) == -1)
    {
        perror("cd");
        return (1);
    }
    var_lst = assemble_name(path, env);
    handle_export(prompt, var_lst, env);
    lst_cleanup(&var_lst, free_token);
    return (0);
}

// minishell$>cd manual_tests/
// free(): invalid pointer
// Aborted (core dumped)
