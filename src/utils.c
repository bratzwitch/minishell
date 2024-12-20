#include "../include/minishell.h"

char	*ft_prompt(void)
{
	char	*input;

	input = readline("minishell$>");
	if (input == NULL)
	{
		printf("vpizdu....\n");
		exit(0);
	}
	return (input);
}
