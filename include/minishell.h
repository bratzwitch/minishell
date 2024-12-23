#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum types
{
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_EXIT_STATUS,
	TOKEN_EOF,
	TOKEN_ERROR // - 10 | you dont use it anywhere, how to check
}					t_token_type;

typedef struct tokens
{
	t_token_type	type;
	char			*value;
}					t_token;

typedef struct s_prompt
{
	char			*input;
	char			*path;
}					t_prompt;

typedef struct s_lexus
{
	char			*input_copy;
	char			*commands;
	char			*options;
	char			*arguments;
	int				token_num;
	int				error_flag;
}					t_lexus;

// SIGNALS
void				sig_handler(int signum);
void				setup_handlers(void);

// COMMANDS
int					handle_builtin_cmds(t_prompt *prompt, char **env);

// INPUT
void				handle_input(t_prompt *prompt, char **env);

// LEXER
void lexer(char *input);
t_token *get_next_token(char **input, int *exit_status);
t_token *create_token(t_token_type type, char *value);
t_token *handle_special_characters(char **current, char ***input);
t_token *handle_dollar_sign(char **input);
t_token *handle_input_redirection(char **input);

// UTILS
char				*ft_prompt(void);
bool ft_isspace(const char c);
bool ft_is_special_character(const char *current);

// FREE
void				free_token(t_token *t);

#endif