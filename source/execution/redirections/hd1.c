#include "minishell.h"

static void hd_forkchild(char *tmpfile, char *delimit)
{
    int fd;
    char *line;

    fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
        pexit("heredoc : open: tmpfile", OPEN_CODE);
    while (true)
    {
        line = readline("heredoc> ");
        if (!line)
            pexit("heredoc: readline", READLINE_CODE);
        if (ft_strlen(line) == ft_strlen(delimit) && 
            !ft_strncmp(line, delimit, ft_strlen(delimit)))
            break ;
        if (write(fd, line, ft_strlen(line)) == -1 ||
            write(fd, "\n", 1) == -1)
            (free(line), close(fd), pexit("heredoc: write", WRITE_CODE));
        free(line);
    }
    free(line);
    close(fd);
    (clear(FREE_ALL), exit(0));
}



void    hd_fork(char *tmpfile, char *delimit)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
        pexit("heredoc: fork", FORK_CODE);
    else if (pid == CHILD)
        hd_forkchild(tmpfile, delimit);
    else
    {
        wait(&status);
        if (WEXITSTATUS(status) > 0)
            (clear(FREE_ALL), exit(WEXITSTATUS(status)));
    }
}
