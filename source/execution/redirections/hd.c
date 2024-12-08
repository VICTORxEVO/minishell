#include "minishell.h"

static char *tmphd_parent(int *pipe)
{
    char buff[BUFSIZ];
    int     read_size;
    int     status;

    wait(&status);
    if (close(pipe[WRITE_END]) < 0)
        pexit("heredoc: close", CLOSE_CODE);
    read_size = read(pipe[READ_END], buff, BUFSIZ);
    buff[read_size] = 0;
    if (read_size < 0)
        pexit("heredoc: read", READ_CODE);
    else if (read_size == 0)
        return (ft_strdup(HERE_DOC_FILE));
    return (ft_strdup(buff));
}


static char *findmktemp(char **path)
{
    int i;
    char *str;

    i = -1;
    if (!path)
    {
        if (access("/usr/bin/mktemp", X_OK) == 0)
            return (ft_strdup("/usr/bin/mktemp"));
    }
    while(path && path[++i])
    {
        str = ft_strjoin(path[i], "mktemp");
        if (access(str, X_OK) == 0)
            return (str);
    }
    return (ft_strdup(HERE_DOC_FILE));
}


static  void tmphd_child(char **env, int *pipe)
{
    char *cmd[2];

    cmd[0] = findmktemp(getcore()->path);
    cmd[1] = NULL;
    if (close(pipe[READ_END]) < 0)
        pexit("heredoc: close", CLOSE_CODE);
    if (dup2(pipe[WRITE_END], STDOUT_FILENO) < 0)
        pexit("heredoc: dup2", CLOSE_CODE);
    if (ft_strncmp(cmd[0], HERE_DOC_FILE, -1) != 0)
        execve(cmd[0], cmd, env);
    if (close(pipe[WRITE_END]) < 0)
        pexit("heredoc: close", CLOSE_CODE);
    clear(FREE_ALL);
    exit (7);
}

static char    *tmphd(char **env)
{
    pid_t pid;
    int pip[2];

    if (pipe(pip) < 0)
        pexit("pipe", PIPE_CODE);
    pid = fork();
    if (pid < 0)
        pexit("", 1);
    else if (pid == CHILD)
        tmphd_child(env, pip);
    return (tmphd_parent(pip));
}

int hd(char *delimit)
{
    int fd;
    char *tmpfile;

    tmpfile = tmphd(getcore()->env);
    hd_fork(tmpfile, delimit);
    fd = open(tmpfile, O_RDONLY);
    if (fd < 0)
        pexit("heredoc: open: tempfile", OPEN_CODE);
    if (unlink(tmpfile) < 0)
        ft_putstr_fd(PRGM_NAME": heredoc: Warning: Failed to remove temporary file", 2);
    clear_1data(tmpfile);
    return (fd);
}
