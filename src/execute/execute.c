#include "../../include/minishell.h"

int execute(t_token *tokens, char *path, char **env)
{
	char **args;
	char *path_exec;

	if (ft_is_special_token(tokens))
		handle_special_tokens(tokens);
	args = lst_to_arr(tokens);
	if (path)
		path_exec = path;
	else
	{
		if (!(path_exec = validator(tokens->value)))
			received_sig = builtins(NULL, tokens, env);
	}
	execve(path_exec, args, env);
	perror("execve");
	exit(2);
}
