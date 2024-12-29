#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <stdlib.h>

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

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token *next;
}					t_token;

typedef struct s_prompt
{
	char			*input;
	char			*path;
	t_token **token_lst;
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
void sig_handler(int signum);
void setup_handlers(void);

// PROCESSES
pid_t create_child_process(void);
void handle_child_process(t_prompt *prompt, char **env);
void handle_parent_process(pid_t id, int *exit_status, t_prompt *prompt);

// COMMANDS
int	handle_builtin_cmds(t_prompt *prompt, char **env);

// INPUT
void handle_input(t_prompt *prompt, char **env);

// LEXER
t_token **lexer(char *input);
t_token *get_next_token(char **input, int *exit_status);
t_token *create_token(t_token_type type, char *value);
t_token *handle_special_characters(char **current, char **input);
t_token *handle_dollar_sign(char **input);
t_token *handle_input_redirection(char **input);

// UTILS
char				*ft_prompt(void);
bool ft_isspace(const char c);
bool ft_is_special_character(const char *current);

// FREE
void free_token(t_token *t);

#endif