#include "minishell.h"

void    pexit(char *msg, short int exit_code)
{
    ft_putstr_fd(PRGM_NAME, 2);
    if (msg[0] == ':')
        (ft_putstr_fd(msg, 2), ft_putstr_fd("\n", 2));
    else
        (ft_putstr_fd(":", 2), perror(msg));
    if (exit_code > 0)
        getcore()->error_flag = true;
    getcore()->exit_code = (unsigned char)exit_code;
}