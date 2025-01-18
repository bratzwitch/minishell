#include "../include/minishell.h"

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
        write(STDERR_FILENO, "Error: sigaction SIGQUIT\n", 26); // what will happen if we add the SIG_DFL handler here instead of the child?
        exit(1);
    }
}
