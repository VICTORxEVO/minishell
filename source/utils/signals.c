#include "minishell.h"

static void sigint_handler_hd(int sig)
{
    (void)sig;
    clear(FREE_ALL);
    close(getcore()->gnl_fd);
    exit(SIG_BASE_CODE + sig);
}

static void sigint_handler(int sig)
{
    if (waitpid(-1, NULL, WNOHANG) == -1)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else
    {
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_redisplay();
    }
    getcore()->exit_code = SIG_BASE_CODE + sig;
    (void)sig;
}

void sighandler(bool mode)
{
    struct sigaction act_int;
    struct sigaction act_quit;

    ft_bzero(&act_int, sizeof(act_int));
    ft_bzero(&act_quit, sizeof(act_quit));

    sigemptyset(&act_int.sa_mask);
    sigemptyset(&act_quit.sa_mask);
    if (mode == SG_HD_MODE)
        act_int.sa_handler = sigint_handler_hd;
    else
        act_int.sa_handler = sigint_handler;
    act_int.sa_flags = SA_RESTART;
    act_quit.sa_handler = SIG_IGN;
    act_quit.sa_flags = 0;
    if (sigaction(SIGINT, &act_int, NULL) == -1 ||
        sigaction(SIGQUIT, &act_quit, NULL) == -1)
        pexit("sigaction()", EXIT_FAILURE, 1);
}
