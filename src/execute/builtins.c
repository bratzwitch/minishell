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

int handle_pwd(t_prompt *prompt)
{
    prompt->path = getcwd(NULL, 0);
    if (!prompt->path)
    {
        perror("pwd");
        return (1);
    }
    printf("%s\n", prompt->path);
    free(prompt->path);
    return (0);
}

int handle_exit(t_prompt *prompt)
{
    printf("Exiting...\n");
    free(prompt->input);
    exit(0);
}

int handle_builtin_cmds(t_prompt *prompt, char *args[], char **env)
{
    if (!strcmp(prompt->input, "env"))
        return (handle_env(env));
    else if (!strcmp(prompt->input, "pwd"))
        return (handle_pwd(prompt));
    else if (!strcmp(prompt->input, "exit"))
        return (handle_exit(prompt));
    else
        return (execute(prompt->input, args, env));
    return (1);
}
