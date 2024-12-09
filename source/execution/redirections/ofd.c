#include "minishell.h"

int     ofd(char *filename, char mode)
{
    int fd;

    if (mode == OUT_RDRT_APP)
    {
        fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
        if (fd < 0)
            pexit(ft_strjoin("open: ", filename), OPEN_CODE);
    }
    else
    {
        fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
        if (fd < 0)
            pexit(ft_strjoin("open: ", filename), OPEN_CODE);
    }
    return (fd);
}