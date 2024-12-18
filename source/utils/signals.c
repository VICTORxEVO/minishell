#include "minishell.h"

static void sigint_handler(int sig)
{
    if (waitpid(-1, NULL, WNOHANG) == -1)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_redisplay();
    }
    (void)sig;
}

void sighandler()
{
    struct sigaction act_int;
    struct sigaction act_quit;

    // Initialize the entire structs to 0
    ft_bzero(&act_int, sizeof(act_int));
    ft_bzero(&act_quit, sizeof(act_quit));

    // Set up SIGINT (Ctrl+C) handler
    act_int.sa_handler = sigint_handler;
    sigemptyset(&act_int.sa_mask);
    act_int.sa_flags = 0; // Remove SA_SIGINFO as we don't need it

    // Set up SIGQUIT (Ctrl+\) handler - completely ignore
    act_quit.sa_handler = SIG_IGN; // Use SIG_IGN instead of custom handler
    sigemptyset(&act_quit.sa_mask);
    act_quit.sa_flags = 0; 

    if (sigaction(SIGINT, &act_int, NULL) == -1)
        pexit("sigaction()", EXIT_FAILURE, 1);
    if (sigaction(SIGQUIT, &act_quit, NULL) == -1)
        pexit("sigaction()", EXIT_FAILURE, 1);
}
