#include "minishell.h"

bool    duping(int ifd, int ofd)
{
    if (ifd > 2)
    {
        if (dup2(ifd, STDIN_FILENO) < 0)
            return (pexit("dup2", DUP2_CODE), false);
        close(ifd);
    }
    if (ofd > 2)
    {
        if (dup2(ofd, STDOUT_FILENO) < 0)
            return (pexit("dup2", DUP2_CODE), false);
        close(ofd);
    }
    return(true);
}

int     ifd(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY, 0666);
    if (fd < 0)
        pexit(filename, OPEN_CODE);
    return (fd);
}
