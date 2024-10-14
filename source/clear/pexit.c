#include "minishell.h"

void    pexit(char *msg, int exit_code)
{
    clear(F_ALL);
    ft_putstr_fd(PRGM_NAME, 2);
    if (msg[0] == ':')
        (ft_putstr_fd(msg, 2), ft_putstr_fd("\n", 2));
    else
        perror(msg);
    exit (exit_code);
}