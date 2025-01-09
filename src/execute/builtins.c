#include "../../include/minishell.h"

int builtins(t_prompt *prompt, char **env)
{
    t_token *tmp = prompt->token_lst;

    if (tmp == NULL)
        return (0);
    if (!strcmp(tmp->value, "env"))
        return (handle_env(env));
    else if (!strcmp(tmp->value, "pwd"))
        return (handle_pwd());
    else if (!strcmp(tmp->value, "exit"))
        return (handle_exit(prompt));
    else if (!strcmp(tmp->value, "cd"))
        return(handle_cd(&prompt->token_lst));
    else if (!strcmp(tmp->value, "echo"))
        return (handle_echo(&prompt->token_lst));
    else if (!strcmp(tmp->value, "export"))
        return(handle_export(prompt, env));
    // else if (!strcmp(tmp->value, "unset"))
    //     return(handle_cd())
    // else
    //     return (execute(tmp->value, env));
    return (1);
}

/*  inter-process communication (IPC)

A pipe is a unidirectional communication channel that connects
    the output of one process to the input of another.
    It allows data to flow in one direction only. */

// ◦ echo with option -n - input
// ◦ cd with only a relative or absolute path - input
// ◦ pwd with no options - done - no input
// ◦ export with no options - input
// ◦ unset with no options - input
// ◦ env with no options or arguments - done - no input
// ◦ exit with no options - done - no input
