#include "../../include/minishell.h"

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

t_token	*lexer(char *input)
{
	t_token	*token_head;
	t_token	*new_token;
	int		trp;
	int		sq;

	sq = 0;
	token_head = NULL;
	new_token = NULL;
	trp = 0;
	if (ft_quotes(input, ft_strlen(input)))
	{
		printf("not closed\n");
		exit(0);
	}
	while (*input)
	{
		if (*input == '\'')
		{
			input++;
			sq = 1;
			while (*input != '\'')
				input++;
			printf("sq closed\n");
			new_token = get_next_token(&input);
			add_token(&token_head, new_token);
			return (token_head);
		}
		while (*input && ft_isspace(*input))
			input++;
		if (*input == '\0')
			break ;
		if (*input == '|' && trp == 0 && sq == 0)
		{
			new_token = create_token(TOKEN_PIPE, "|");
			add_token(&token_head, new_token);
			input++;
			continue ;
		}
		new_token = get_next_token(&input);
		if (!new_token || new_token->type == TOKEN_ERROR)
		{
			free_token(new_token);
			lst_cleanup(&token_head, free_token);
			return (NULL);
		}
		add_token(&token_head, new_token);
	}
	return (token_head);
}

// t_token *lexer(char *input)
// {
//     t_token *token_head = NULL;
//     t_token *new_token = NULL;

// 	token_head  = NULL;
// 	new_token = NULL;
//     while (*input)
//     {
//         while (*input && ft_isspace(*input))
//             input++;
//         if (*input == '\0')
//             break ;
//         new_token = get_next_token(&input);
//         if (!new_token || new_token->type == TOKEN_ERROR)
//         {
//             free_token(new_token);
//             lst_cleanup(&token_head, free_token);
//             return (NULL);
//         }
//         add_token(&token_head, new_token);
//     }
//     return (token_head);
// }

// ⣿⣿⣿⣿⣿⣿⣿⠿⠿⢛⣋⣙⣋⣩⣭⣭⣭⣭⣍⣉⡛⠻⢿⣿⣿⣿⣿
// ⣿⣿⣿⠟⣋⣥⣴⣾⣿⣿⣿⡆⣿⣿⣿⣿⣿⣿⡿⠟⠛⠗⢦⡙⢿⣿⣿
// ⣿⡟⡡⠾⠛⠻⢿⣿⣿⣿⡿⠃⣿⡿⣿⠿⠛⠉⠠⠴⢶⡜⣦⡀⡈⢿⣿
// ⡿⢀⣰⡏⣼⠋⠁⢲⡌⢤⣠⣾⣷⡄⢄⠠⡶⣾⡀⠀⣸⡷⢸⡷⢹⠈⣿
// ⡇⢘⢿⣇⢻⣤⣠⡼⢃⣤⣾⣿⣿⣿⢌⣷⣅⡘⠻⠿⢛⣡⣿⠀⣾⢠⣿
// ⣷⠸⣮⣿⣷⣨⣥⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢁⡼⠃⣼⣿
// ⡟⠛⠛⠛⣿⠛⠛⢻⡟⠛⠛⢿⡟⠛⠛⡿⢻⡿⠛⡛⢻⣿⠛⡟⠛⠛⢿
// ⡇⢸⣿⠀⣿⠀⠛⢻⡇⠸⠃⢸⡇⠛⢛⡇⠘⠃⢼⣷⡀⠃⣰⡇⠸⠇⢸
// ⡇⢸⣿⠀⣿⠀⠛⢻⡇⢰⣿⣿⡇⠛⠛⣇⢸⣧⠈⣟⠃⣠⣿⡇⢰⣾⣿
// ⣿⣿⣿⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢋⣿⠙⣷⢸⣷⠀⣿⣿⣿
// ⣿⣿⣿⡇⢻⣿⣿⣿⡿⠿⢿⣿⣿⣿⠟⠋⣡⡈⠻⣇⢹⣿⣿⢠⣿⣿⣿
// ⣿⣿⣿⣿⠘⣿⣿⣿⣿⣯⣽⣉⣿⣟⣛⠷⠙⢿⣷⣌⠀⢿⡇⣼⣿⣿⣿
// ⣿⣿⣿⡿⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡙⢿⢗⣀⣁⠈⢻⣿⣿
// ⣿⡿⢋⣴⣿⣎⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡉⣯⣿⣷⠆⠙⢿
// ⣏⠀⠈⠧⠡⠉⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠉⢉⣁⣀⣀⣾