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
        return (handle_cd(tokens, env));
    else if (!strcmp(tokens->value, "echo"))
        return (handle_echo(tokens));
    else if (!strcmp(tokens->value, "export"))
        return (handle_export(tokens, env));
    else if (!strcmp(tokens->value, "unset"))
        return (handle_unset(tokens, env));
    return (2);
}
