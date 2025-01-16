#include "../../include/minishell.h"

int builtins(t_prompt *prompt, t_token *tokens, char **env)
{
    if (tokens == NULL)
        return (2);
    if (ft_is_special_token(tokens))
        handle_special_tokens(tokens);
    if (!strcmp(tokens->value, "env"))
        return (handle_env(env));
    else if (!strcmp(tokens->value, "pwd"))
        return (handle_pwd());
    else if (!strcmp(tokens->value, "exit"))
        return (handle_exit(prompt));
    else if (!strcmp(tokens->value, "cd"))
        return (handle_cd(prompt, tokens, env));
    else if (!strcmp(tokens->value, "echo"))
        return (handle_echo(tokens));
    else if (!strcmp(tokens->value, "export"))
        return (handle_export(prompt, tokens, env));
    else if (!strcmp(tokens->value, "unset"))
        return (handle_unset(tokens, env));
    return (2);
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
