#include "minishell.h"

void    pexit(t_gc **gc, char *msg, int exit_code)
{
    clear(gc, F_ALL);
    perror(msg);
    exit (exit_code);
}