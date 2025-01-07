#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

enum					e_token_type
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
	TOKEN_ERROR
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_prompt
{
	char *input; // requires freeing in the end
	char *path;  // needs to be freed
	char				*exported_vars;
	t_token *token_lst; // requires freeing in the end
}						t_prompt;

typedef struct s_lexus
{
	char				*input_copy;
	char				*commands;
	char				*options;
	char				*arguments;
	int					token_num;
	int					error_flag;
}						t_lexus;

// SIGNALS
void					sig_handler(int signum);
void					setup_handlers(void);

// PROCESSES
pid_t					create_child_process(void);
void					handle_child_process(t_prompt *prompt, char **env);
void					handle_parent_process(pid_t id, int *exit_status,
							t_prompt *prompt);

// EXEC
int						execute(t_prompt *prompt, char **env);
int						validator(t_prompt *prompt, char *cmd_name);
int						handle_builtins(t_prompt *prompt, char **env);
char					*find_command(char *cmd_name, char *env_path);

// BUILT-INS
int						handle_echo(t_token **token);
int						handle_cd(t_token **token);
int						handle_env(char **env);
int						handle_pwd(void);
int						handle_exit(t_prompt *prompt);
int						handle_export(t_prompt *prompt, char **env);

// LEXER
t_token					*lexer(char *input);
t_token					*get_next_token(char **input);
t_token					*create_token(enum e_token_type type, char *value);
t_token					*handle_special_characters(char **current,
							char **input);
t_token					*handle_dollar_sign(char **input);
t_token					*handle_input_redirection(char **input);

// REDIRECTIONS
int						input_redirection(const char *file_name);
int						output_redirection(const char *file_name);

// PIPE
void					piping(t_prompt *prompt, int pipe_count, char **env);
int						count_pipes(t_token *token_lst);

// UTILS
char					**lst_to_arr(t_token *token_lst);
bool					ft_isspace(const char c);
bool					ft_is_special_character(const char *current);
bool					is_history(char *input);
void					lst_add_back(t_token **lst, t_token *new);
void					lst_print(t_token *token_lst);

// FREE
void					ft_free(char **values);
void					free_token(t_token *t);
void					cleanup(t_prompt *prompt);
void					lst_cleanup(t_token **head, void (*del)(t_token *));

#endif