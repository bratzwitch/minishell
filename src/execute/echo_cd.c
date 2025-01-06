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
        path = (*token)->next->value;
    if (chdir(path) == -1)
    {
        perror("cd");
        return (1);
    }
    return (0);
}
