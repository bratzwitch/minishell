#ifndef MINISHELL_H
# define MINISHELL_H


#include "../libft/includes/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_prompt {
    char *input;
    char *path;
} t_prompt;

typedef struct s_lexus
{
    char *input_copy;
    char *commands;
    char *options;
    char *arguments;
    int token_num;
    int error_flag;
}   t_lexus;
// SIGNALS
void	sig_handler(int signum);
void	setup_handlers(void);

// COMMANDS
int	handle_builtin_cmds(t_prompt *prompt, char **env);
void tokenise(t_prompt *prompt);

// INPUT
void	handle_input(t_prompt *prompt, char **env);

// UTILS
char	*ft_prompt(void);

#endif