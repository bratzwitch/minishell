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
