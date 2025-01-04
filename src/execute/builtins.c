#include "../../include/minishell.h"

int handle_builtins(t_prompt *prompt, t_token *tokens, char *args[], char **env)
{
    t_token *tmp = tokens;

    if (tmp == NULL)
        return (0);
    if (!strcmp(tmp->value, "env"))
        return (handle_env(env));
    else if (!strcmp(tmp->value, "pwd"))
        return (handle_pwd());
    else if (!strcmp(tmp->value, "exit"))
        return (handle_exit(prompt));
    else if (!strcmp(tmp->value, "cd"))
        return(handle_cd(&tokens));
    else if (!strcmp(tmp->value, "echo"))
        return (handle_echo(&tokens));
    // else if (!strcmp(tmp->value, "export"))
    //     return(handle_export())
    // else if (!strcmp(tmp->value, "unset"))
    //     return(handle_cd())
    else
        return (execute(tmp->value, args, env));
    return (1);
}

// ◦ echo with option -n - input
// ◦ cd with only a relative or absolute path - input
// ◦ pwd with no options - done - no input
// ◦ export with no options - input
// ◦ unset with no options - input
// ◦ env with no options or arguments - done - no input
// ◦ exit with no options - done - no input
