#include "minishell.h"

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



static void hd_forkchild(char *tmpfile, char *delimit)
{
    int fd;
    char *line;
    unsigned int count;

    count = 1;
    fd = open(tmpfile, O_WRONLY | O_CREAT, 0666);
    if (fd < 0)
        (pexit("heredoc: tmpfile", OPEN_CODE, EXIT));
    while (true)
    {
        line = readline("heredoc> ");
        if (hd_handleline(line, delimit, fd, count) == 1)
            break;
        count++;
    }
    (close(fd), clear(FREE_ALL), exit(0));
}

static void    hd_fork(char *tmpfile, char *delimit)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
        pexit("heredoc: fork", FORK_CODE, EXIT);
    else if (pid == CHILD)
        hd_forkchild(tmpfile, delimit);
    else
    {
        wait(&status);
        if (WEXITSTATUS(status) > 0)
            (clear(FREE_ALL), exit(WEXITSTATUS(status)));
    }
}

int hd(char *delimit)
{
    int fd;
    char *tmpfile;

    tmpfile = ft_strjoin("/tmp/hdtmp.", ft_itoa(getpid()));
    hd_fork(tmpfile, delimit);
    fd = open(tmpfile, O_RDONLY);
    if (fd < 0)
        pexit("heredoc: tempfile", OPEN_CODE, 0);
    if (unlink(tmpfile) < 0)
        ft_putstr_fd(PRGM_NAME": heredoc: Warning: Failed to remove temporary file", 2);
    clear_1data(tmpfile);
    return (fd);
}
