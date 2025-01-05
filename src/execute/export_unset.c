#include "../../include/minishell.h"

int handle_export(t_token *token)
{
    t_token *tmp = token;

    (void)tmp;
    if (setenv("PWD", "HelloWorld", 1) == 0)
        printf("PWD set to: %s\n", getenv("PWD"));
    else
        perror("setenv");
    return (0);
}
