#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

typedef struct s_prompt {
    char *input;
    char *path;
} t_prompt;

// SIGNALS
void	sig_handler(int signum);
void	setup_handlers(void);

// COMMANDS
int	handle_builtin_cmds(t_prompt *prompt, char **env);

#endif