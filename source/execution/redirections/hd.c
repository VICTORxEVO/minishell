#include "minishell.h"

static char getunique(void)
{
    static char num;

    if (num == 90)
        num = 0;
    num += 65;
    return (num);
}

static bool hd_handleline(char *line, char *delimit, int fd, unsigned int count)
{
    if (!line)
    {
        printf(PRGM_NAME": warning: here-document at line %u delimited by end-of-file (wanted `%s')\n", count, delimit);
        return (1);
    }
    if (!ft_strncmp(line, delimit, -1))
        return (free(line), 1);
    (ft_putstr_fd(line, fd), ft_putstr_fd("\n", fd));
    return (0);
}

static bool hd_reader_loop(char *tmpfile, char *delimit)
{
    int fd;
    char *line;
    unsigned int count;

    count = 1;
    fd = open(tmpfile, O_WRONLY | O_CREAT, 0666);
    if (fd < 0)
        return (pexit("heredoc: tmpfile", OPEN_CODE, 0), 1);
    while (true)
    {
        line = readline("heredoc> ");
        if (hd_handleline(line, delimit, fd, count) == 1)
            break;
        count++;
    }
    return (close(fd), 0);
}

int hd(char *delimit)
{
    int     fd;
    char    *tmpfile;

    tmpfile = ft_strjoin("/tmp/hdtmp.", ft_itoa(getpid()));
    tmpfile[ft_strlen(tmpfile) - 1] = getunique();
    if (hd_reader_loop(tmpfile, delimit) == 1)
        return(-1);
    fd = open(tmpfile, O_RDONLY);
    if (fd < 0)
        pexit("heredoc: tempfile", OPEN_CODE, 0);
    if (unlink(tmpfile) < 0)
        ft_putstr_fd(PRGM_NAME": heredoc: Warning: Failed to remove temporary file", 2);
    clear_1data(tmpfile);
    return (fd);
}
