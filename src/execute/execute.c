#include "../../include/minishell.h"

int execute(char *cmd_name, char *args[], char **env)
{
	char *path;
	char *arg_single[2] = {cmd_name, NULL};
	(void)args;

	path = find_command(cmd_name, getenv("PATH")); // dont forget to free later
	if (!path)
	{
		printf("Command not recognised: %s\n", cmd_name);
		return (127);
	}
	printf("Found the command at: %s\n", path);
	execve(path, arg_single, env);
	free(path);
	return(0);
}
