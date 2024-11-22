#include "minishell.h"

void    pexit(char *msg, int exit_code)
{
    ft_putstr_fd(PRGM_NAME, 2);
    if (msg[0] == ':')
        (ft_putstr_fd(msg, 2), ft_putstr_fd("\n", 2));
    else
        (ft_putstr_fd(":", 2), perror(msg));
    clear(FREE_ALL);
    (void)exit_code;
    exit (exit_code);
}