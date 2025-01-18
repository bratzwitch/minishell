/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:44:13 by vmoroz            #+#    #+#             */
/*   Updated: 2025/01/18 16:12:27 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

extern volatile sig_atomic_t	g_received_sig;

enum							e_token_type
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

typedef struct s_redirection
{
	enum e_token_type			type;
	int							(*handler)(const char *value);
}								t_redirection;

typedef struct s_token
{
	enum e_token_type			type;
	char						*value;
	struct s_token				*next;
}								t_token;

typedef struct s_pipe
{
	t_token						*current_tokens;
	t_token						*list1;
	t_token						*list2;
	pid_t						pid;
	int							fd[2];
	int							pipe_count;
	int							prev_pipe;
	int							i;
}								t_pipe;

typedef struct s_prompt
{
	char						*input;
	char						*path;
	char						**env_copy;
	t_token						*token_lst;
	int							exit_status;
	int							fdin_copy;
	int							fdout_copy;
}								t_prompt;

// SIGNALS
void							sig_handler(int signum);
void							setup_handlers(void);
void							setup_dfl_signals(void);
void							ignore_signals(void);

// PROCESSES
pid_t							create_child_process(void);
void							handle_child_process(t_prompt *prompt,
									char **env);
void							handle_parent_process(pid_t id,
									int *exit_status, t_prompt *prompt);

// EXEC
int								execute(t_token *tokens, char *path,
									char **env);
char							*validator(char *cmd_name);
int								builtins(t_prompt *prompt, t_token *tokens,
									char **env);
char							*find_command(char *cmd_name, char *env_path);
void							handle_special_tokens(t_token *tokens);

// BUILT-INS
int								handle_echo(t_token *token);
int								handle_cd(t_token *token, char **env);
int								handle_env(char **env);
int								handle_pwd(void);
int								handle_exit(t_prompt *prompt);
int								handle_export(t_token *tokens, char ***env);
int								handle_unset(t_token *tokens, char **env);
int								find_var(char *name, char **env);
char							*format_env_var(char *name, char *value);

// LEXER
char							*process_whitespace(char *current);
char							*process_current_char(char **current,
									char *final_str);
char							*handle_dollar(char **current, char *final_str);
t_token							*lexer(char *input);
t_token							*get_next_token(char **input);
t_token							*create_token(enum e_token_type type,
									char *value);
t_token							*handle_special_characters(char **current,
									char **input);
t_token							*handle_input_redirection(char **input);
char							*handle_single_quotes(char **input,
									char *final_str);
char							*handle_double_quote(char **input,
									char *final_str);
int								ft_quotes(char *str, int size);
char							*get_env_variable(char **current,
									char *var_start);
t_token							*handle_argument(char **input);
char							*dollar(char **current, char *final_str,
									char **start);
char							*append_to_final_str(char *final_str,
									const char *start, size_t len);

// REDIRECTIONS
int								heredoc_redirection(const char *delimiter);
int								input_redirection(const char *file_name);
int								output_redirection(const char *file_name);
int								append_redirection(const char *file_name);
int								save_stdinout(int *fdin_copy, int *fdout_copy);
void							restore_stdinout(int *fdin_copy,
									int *fdout_copy);

// PIPE
void							piping(t_prompt *prompt);
int								count_pipes(t_token *token_lst);

// UTILS
char							*ft_prompt(t_prompt *prompt);
int								ft_is_valid_identifier(char *name);
char							*get_var_name(const char *name);
char							**expand_env(char **env, int new_size);
int								get_env_size(char **env);
void							replace_existing_var(char ***env, char *new_var,
									int index);
char							**lst_to_arr(t_token *token_lst);
bool							ft_isspace(const char c);
bool							ft_is_special_character(const char *current);
void							lst_add_back(t_token **lst, t_token *new);
char							**lst_to_arr(t_token *tokens);
int								is_pipe(t_token *head);
enum e_token_type				ft_is_special_token(t_token *head);
void							split_tokens(t_token *head, t_token **list1,
									t_token **list2,
									enum e_token_type TOKEN_TYPE);
void							add_token(t_token **head, t_token *new_token);
bool							ft_is_quotes(const char *current);
void							wait_for_children(int child_count);
void							create_pipes(int i, int pipe_count, int fd[2]);
int								create_pipe(int pipe_fd[2]);
int								count_tokens(t_token *lst);
bool							ft_is_num(char *str);
void							concatenate_tokens(t_token **tokens,
									t_token *list2);
char							**copy_env(char **env);

// void	lst_print(t_token *token_lst); // tests
// void	print_args(char **args);       // tests

// FREE
void							ft_free(char **values);
void							free_token(t_token *t);
void							cleanup(t_prompt *prompt);
void							lst_cleanup(t_token **head,
									void (*del)(t_token *));
void							free_prompt(t_prompt *prompt);

#endif