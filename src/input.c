#include "../include/minishell.h"

char	*ft_prompt(void)
{
	char	*input;

	input = readline("minishell$>");
	if (input == NULL) // detect EOF; handle ctrl+D
	{
		printf("vpizdu...\n");
		exit (0);
	}
	return (input);
}

void	handle_input(t_prompt *prompt, t_token **tokens, char *args[], char **env)
{
	if (prompt->input[0] == '\0')
	{
		printf("Input is empty just like my bank account.\n");
		free(prompt->input);
		return ;
	}
	if (handle_builtins(prompt, tokens, args, env) != 0)
	{
		free(prompt->input);
		printf("Buildins?? : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	free(prompt->input);
}
