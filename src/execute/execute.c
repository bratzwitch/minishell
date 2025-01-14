#include "../../include/minishell.h"

char *build_path(char *dir, char *cmd_name)
{
	char *with_slash;
	char *full_path;

	with_slash = ft_strjoin(dir, "/");
	if (!with_slash)
		return (NULL);
	full_path = ft_strjoin(with_slash, cmd_name);
	free(with_slash);
	return (full_path);
}

char *find_command(char *cmd_name, char *env_path)
{
	char **dirs;
	char *full_path;
	int i;

	if (!env_path)
		return (NULL);
	dirs = ft_split(env_path, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = build_path(dirs[i], cmd_name);
		if (!full_path)
		{
			free(dirs);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			ft_free(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free(dirs);
	return (NULL);
}

enum e_token_type ft_is_special_token(t_token *head)
{
	t_token *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_REDIRECT_OUT || tmp->type == TOKEN_HEREDOC || tmp->type == TOKEN_REDIRECT_APPEND)
			return (tmp->type);
		tmp = tmp->next;
	}
	return (-1);
}

char *validator(char *cmd_name)
{
	char *path;

	path = find_command(cmd_name, getenv("PATH")); // dont forget to free later
	if (!path)
	{
		free(path);
		return (NULL);
	}
	return (path);
}

void handle_special_tokens(t_token *tokens)
{
	t_token *current = tokens;
	t_token *list1 = NULL;
	t_token *list2 = NULL;
	t_redirection redir[] = {
		{TOKEN_REDIRECT_IN, input_redirection},
		{TOKEN_REDIRECT_OUT, output_redirection},
		{TOKEN_HEREDOC, heredoc_redirection},
		// {TOKEN_REDIRECT_APPEND, },
		{0, NULL}};
	int i;

	while (current)
	{
		i = 0;
		while (redir[i].handler != NULL)
		{
			if (current->type == redir[i].type && redir[i].type > 0)
			{
				split_tokens(current, &list1, &list2, redir[i].type);
				if (!list1 || !list1->value || !list2 || !list2->value)
				{
					fprintf(stderr, "minishell: syntax error near unexpected token '%s'\n", current->value);
					return;
				}
				if (redir[i].handler(list2->value) == -1)
				{
					printf("Redirection failed for %s\n", strerror(errno));
					return;
				}
				current = list2;
				break;
			}
			i++;
		}
		current = current->next;
	}
	split_tokens(tokens, &list1, &list2, ft_is_special_token(tokens));
}

int execute(t_token *tokens, char *path, char **env)
{
	char **args;
	char *path_exec;

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
