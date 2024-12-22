#include "minishell.h"

static char getunique(void)
{
    static char num;

    if (num == 123)
        num = 0;
    if (num == 0)
        num += 96;
    num++;
    return (num);
}

static bool hd_handleline(char *line, char *delimit, int fd)
{
    if (!line)
    {
        printf(PRGM_NAME": warning: here-document delimited by end-of-file (wanted `%s')\n", delimit);
        return (1);
    }
    else if (!ft_strncmp(line, delimit, -1))
        return (1);
    else if (needexpand(line, NULL))
        line = expand_dollar(line);
    (ft_putstr_fd(line, fd), ft_putstr_fd("\n", fd));
    return (0);
}

static void hd_forkchild(char *tmpfile, char *delimit)
{
    int fd;
    char *line;

    close_allhd(getcore()->lexer);
    fd = open(tmpfile, O_WRONLY | O_CREAT, 0666);
    if (fd < 0)
        (pexit("heredoc: tmpfile", 2, EXIT));
    getcore()->gnl_fd = fd;
    while (true)
    {
        line = readline("heredoc> ");
        if (line)
            gc_add_node(line);
        if (hd_handleline(line, delimit, fd) == 1)
            break;
    }
    (close(fd), clear(FREE_ALL), exit(0));
}

static int    hd_fork(char *tmpfile, char *delimit)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
        pexit("heredoc: fork", FORK_CODE, EXIT);
    else if (pid == CHILD)
        (sighandler(SG_HD_MODE), hd_forkchild(tmpfile, delimit));
    else
    {
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status))
            return(SIG_BASE_CODE + WTERMSIG(status));
        else if (WEXITSTATUS(status) == 130)
            return (WEXITSTATUS(status));
        else if (WEXITSTATUS(status) > 0)
            return ((clear(FREE_ALL), exit(WEXITSTATUS(status))), 1);
    }
    return (0);
}

int hd(char *delimit)
{
    int fd;
    char *tmpfile;
    char *term_name;
    int res;

    term_name = ttyname(STDERR_FILENO);
    term_name = &term_name[ft_strlen(term_name) - 1];
    tmpfile = ft_strjoin("/tmp/hdtmp. ", term_name);
    tmpfile[ft_strlen(tmpfile) - 2] = getunique();
    res = hd_fork(tmpfile, delimit);
    if (res > SIG_BASE_CODE)
        return(unlink(tmpfile), -1);
    fd = open(tmpfile, O_RDONLY);
    if (fd < 0)
        pexit("heredoc: tempfile", OPEN_CODE, 0);
    if (unlink(tmpfile) < 0)
        ft_putstr_fd(PRGM_NAME": heredoc: Warning: Failed to remove temporary file", 2);
    return (fd);
}
