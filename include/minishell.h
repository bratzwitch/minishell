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

void sig_handler(int signum);
void	prompt(char *input);

#endif