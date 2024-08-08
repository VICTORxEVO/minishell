#include "minishell.h"

void    pexit(t_core *core, char *msg, int exit_code)
{
    clear(&core->gc_tmp);
    clear(&core->gc_perm);
    perror(msg);
    exit (exit_code);
}