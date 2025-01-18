#include "../include/minishell.h"

void setup_dfl_signals(void)
{
    struct sigaction sa_default;

    sigemptyset(&sa_default.sa_mask);
    sa_default.sa_flags = 0;
    sa_default.sa_handler = SIG_DFL;
    if (sigaction(SIGINT, &sa_default, NULL) == -1)
        write(STDERR_FILENO, "Error: sigaction SIGQUIT\n", 26);
}

void ignore_signals(void)
{
    struct sigaction sa_ignore;

    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;
    sa_ignore.sa_handler = SIG_IGN;
    if (sigaction(SIGINT, &sa_ignore, NULL) == -1)
        write(STDERR_FILENO, "Error: sigaction SIGINT\n", 25);
}

void sig_handler(int signum)
{
    g_received_sig = 128 + signum;
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void setup_handlers(void)
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = sig_handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        write(STDERR_FILENO, "Error: sigaction SIGINT\n", 25);
        exit(1);
    }
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
    {
        write(STDERR_FILENO, "Error: sigaction SIGQUIT\n", 26);
        exit(1);
    }
}
