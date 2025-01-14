#include "../include/minishell.h"

// this data type ensures that the variable can be safely read and written even in the presence of asynchronous signals.
//      The volatile keyword is used to inform the compiler that a variable's value may change at any time,
//      without any action being taken by the code the compiler finds nearby. (+ The compiler might optimize away reads and writes to variables if it assumes their values do not change unexpectedly.)

/* Asynchronous signals are events that can occur at any time, interrupting the normal flow of a program.
These signals are typically generated by external events or by the operating system. Examples:
SIGINT: Interrupt signal (e.g., from pressing Ctrl+C).
SIGTERM: Termination signal.
SIGALRM: Alarm clock signal.
SIGCHLD: Child process terminated or stopped. */

void sig_handler(int signum)
{
    (void)signum;
    rl_replace_line("", 0);
    rl_on_new_line();
    write(STDOUT_FILENO, "\n", 1);
    rl_redisplay();
}
 
// void global_handler(int signum)
// {
//     received_sig = signum;
// }

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
        write(STDERR_FILENO, "Error: sigaction SIGQUIT\n", 25);
        exit(1);
    }
    // sa.sa_hadler = global_handler;
    // if (sigaction(, &sa, NULL) == -1)
    // {
    //     write(STDERR_FILENO, "Error: sigaction \n", 25);
    //     exit(1);
    // }
}
