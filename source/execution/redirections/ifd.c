#include "minishell.h"

bool    duping(int ifd, int ofd)
{
    if (ifd > 2)
    {
        if (dup2(ifd, STDIN_FILENO) < 0)
            return (pexit("dup2", DUP2_CODE, 0), false);
        close(ifd);
    }
    if (ofd > 2)
    {
        if (dup2(ofd, STDOUT_FILENO) < 0)
            return (pexit("dup2", DUP2_CODE, 0), false);
        close(ofd);
    }
    return(true);
}

int     ifd(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY, 0666);
    if (fd < 0)
        pexit(filename, GNRL_CODE, 0);
    return (fd);
}
