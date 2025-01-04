#include "../../include/minishell.h"

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

    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("Current working directory: %s\n", cwd);
    else
        perror("getcwd() error");

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

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("New working directory: %s\n", cwd);
    else
        perror("getcwd() error");
        
    return (0);
}
