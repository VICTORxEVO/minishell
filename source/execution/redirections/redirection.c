#include "minishell.h"

int     redirection(char *filename, char mode, int oldfd)
{
    if (mode == HERE_DOC)
        return (hd(filename));
    else if (mode == IN_RDRT)
        return (ifd(filename));
    else
        return (ofd(filename, mode));
    if (oldfd > 2)
        close (oldfd);
}