#include "minishell.h"

void    pexit(char *msg, int exit_code)
{
    t_all *core;

    core = get_core();
    clear(F_ALL);
    perror(msg);
    exit (exit_code);
}