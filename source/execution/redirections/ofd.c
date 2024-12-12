#include "minishell.h"

int     ofd(char *filename, char mode)
{
    int fd;

    if (mode == OUT_RDRT_OW)
    {
        fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
        if (fd < 0)
            pexit(ft_strjoin("open: ", filename), OPEN_CODE, 0);
    }
    else
    {
        fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
        if (fd < 0)
            pexit(ft_strjoin("open: ", filename), OPEN_CODE, 0);
    }
    return (fd);
}