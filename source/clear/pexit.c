#include "minishell.h"

void    pexit(char *msg, int exit_code)
{
    t_all *core;

    core = get_core();
    clear(F_ALL);
    ft_putstr_fd(PRGM_NAME, 2);
    if (msg[0] == ':')
        ft_putstr_fd(msg, 2);
    else
        perror(msg);
    exit (exit_code);
}