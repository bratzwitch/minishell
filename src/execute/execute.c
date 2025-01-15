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
		path_exec = validator(tokens->value);
	execve(path_exec, args, env);
	perror("execve");
	exit(1);
}
