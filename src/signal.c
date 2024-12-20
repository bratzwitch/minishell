#include "../include/minishell.h"
#define _XOPEN_SOURCE 700

void sig_handler(int signum)
{
    (void)signum;
    rl_replace_line("", 0);
    rl_on_new_line();
    write(STDOUT_FILENO, "\n", 1);
    rl_redisplay();
}

void setup_handlers(void)
{
    struct sigaction sa;

    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        write(STDERR_FILENO, "Error sigaction SIGUSR1\n", 25);
        exit(1);
    }
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        write(STDERR_FILENO, "Error sigaction SIGUSR2\n", 25);
        exit(1);
    }
    signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}