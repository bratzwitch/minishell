#include "../../include/minishell.h"

t_token *lexer(char *input)
{
    t_token *token_head;
    t_token *new_token;

    token_head = NULL;
    new_token = NULL;
    if (ft_quotes(input, ft_strlen(input)))
    {
        printf("Quotes not closed. God saw.\n");
        return(NULL);
    }
    while (*input)
    {
        while (*input && ft_isspace(*input))
            input++;
        new_token = get_next_token(&input);
        if (new_token->type == TOKEN_ERROR)
        {
            free_token(new_token);
            lst_cleanup(&token_head, free_token);
            return (NULL);
        }
        add_token(&token_head, new_token);
    }
    // lst_print(token_head); // tests
    return (token_head);
}

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