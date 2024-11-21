#include "minishell.h"

int     ofd(char *filename, char mode)
{
    if (mode == OUT_RDRT_APP)
        (void)mode; //appende case here
    else
        (void)mode; //overright case here
    (void)filename;
}