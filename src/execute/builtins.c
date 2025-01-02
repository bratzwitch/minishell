#include "../../include/minishell.h"

int handle_env(char **env)
{
    if (!env)
        return (1);
    while (*env)
    {
        printf("%s\n", *env);
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
    printf("Exiting...\n");
    free(prompt->input); // check for double frees at 42
    exit(0);
}

int count_args(char *args[])
{
    int i;

    i = 0;
    while (args[i] != NULL)
        i++;
    return (i);
}

int handle_echo(t_token **token)
{
    t_token *tmp;
    bool is_n;

    tmp = NULL;
    if (*token)
        tmp = (*token)->next;
    is_n = false;
    if (tmp && !strcmp(tmp->value, "-n"))
    {
        rl_replace_line("", 0);
        rl_on_new_line();
        is_n = true;
        tmp = tmp->next;
    }
    while (tmp)
    {
        ft_putstr_fd(tmp->value, 1);
        if (tmp->next)
            ft_putchar_fd(' ', 1);
        tmp = tmp->next;
    }
    if (!is_n)
        ft_putchar_fd('\n', 1);
    return (0);
}

int handle_cd(t_token **token)
{
    char *path;
    char *home;

    if (!(*token)->next)
    {
        home = getenv("HOME");
        if (!home)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return (1);
        }
        path = home;
    }
    else
        path = (*token)->next->value; // Get the path from the next token
    if (chdir(path) == -1)
    {
        perror("cd");
        return (1);
    }
    return (0);
}

int handle_builtins(t_prompt *prompt, t_token **tokens, char *args[], char **env)
{
    t_token *tmp = *(tokens);

    if (!strcmp(tmp->value, "env"))
        return (handle_env(env));
    else if (!strcmp(tmp->value, "pwd"))
        return (handle_pwd());
    else if (!strcmp(tmp->value, "exit"))
        return (handle_exit(prompt));
    else if (!strcmp(tmp->value, "cd"))
        return(handle_cd(tokens));
    else if (!strcmp(tmp->value, "echo"))
        return (handle_echo(tokens));
    // else if (!strcmp(tmp->value, "export"))
    //     return(handle_export())
    // else if (!strcmp(tmp->value, "unset"))
    //     return(handle_cd())
    else
        return (execute(tmp->value, args, env));
    return (1);
}

// ◦ echo with option -n
// ◦ cd with only a relative or absolute path
// ◦ pwd with no options - done
// ◦ export with no options
// ◦ unset with no options
// ◦ env with no options or arguments - done
// ◦ exit with no options - done
