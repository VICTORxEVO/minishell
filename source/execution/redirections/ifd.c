#include "minishell.h"

int     ifd(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY, 0666);
    if (fd < 0)
        pexit(ft_strjoin("open: ", filename), OPEN_CODE);
    return (fd);
}
