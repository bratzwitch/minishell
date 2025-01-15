#include "../../../include/minishell.h"

int handle_echo(t_token *token, int fd)
{
    t_token *tmp;
    bool is_n;

    tmp = NULL;
    if (token)
        tmp = token->next;
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
        tmp = tmp->next;
    }
    if (!is_n)
        ft_putchar_fd('\n', 1);
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("Error redirecting input.");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}
