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

typedef struct s_prompt
{
	char			*input;
	char			*path;
}					t_prompt;

typedef enum types
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_EXIT_STATUS,
	TOKEN_EOF,
	TOKEN_ERROR
}					t_token_type;

typedef struct tokens
{
	t_token_type	type;
	char			*value;
}					t_token;

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
void				tokenise(t_prompt *prompt);

// INPUT
void				handle_input(t_prompt *prompt, char **env);

// LEXER
void				lexer(char *input, char **env);
t_token				*get_next_token(char **input, char **env, int *exit_status);

// UTILS
char				*ft_prompt(void);
bool				ft_isspace(char c);

// FREE
void				free_token(t_token *t);

#endif