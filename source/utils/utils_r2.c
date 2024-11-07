#include "minishell.h"

void    addoldhistory(void)
{
    char *home;
    

    home = getenv("HOME");
    if (!home)
        exit (200);
}