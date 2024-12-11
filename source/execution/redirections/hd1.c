#include "minishell.h"

static void hd_forkchild(char *tmpfile, char *delimit)
{
    int fd;
    char *line;

    fd = open(tmpfile, O_WRONLY, 0666);
    if (fd < 0)
        (pexit("heredoc : tmpfile", OPEN_CODE, EXIT));
    while (true)
    {
        line = readline("heredoc> ");
        if (!line)
        {//to do handle the EOF properly with a message
            pexit("heredoc: readline", READLINE_CODE, EXIT);
        }
        if (ft_strlen(line) == ft_strlen(delimit) && 
            !ft_strncmp(line, delimit, ft_strlen(delimit)))
            break ;
        if (write(fd, line, ft_strlen(line)) == -1 ||
            write(fd, "\n", 1) == -1)
            (free(line), close(fd), pexit("heredoc: write", WRITE_CODE, EXIT));
        free(line);
    }
    (free(line), close(fd));
    (clear(FREE_ALL), exit(0));
}



void    hd_fork(char *tmpfile, char *delimit)
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
