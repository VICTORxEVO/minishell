#include "minishell.h"

static char *tmphd_parent(int *pipe)
{
    char buff[BUFSIZ];
    int     read_size;
    int     status;

    wait(&status);
    if (close(pipe[WRITE_END]) < 0)
        pexit("heredoc: close", CLOSE_CODE, 0);
    read_size = read(pipe[READ_END], buff, BUFSIZ);
    buff[read_size] = 0;
    if (read_size < 0)
        pexit("heredoc: read", READ_CODE, 0);
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
        (pexit("heredoc: close", CLOSE_CODE, EXIT));
    if (dup2(pipe[WRITE_END], STDOUT_FILENO) < 0)
        (pexit("heredoc: dup2", CLOSE_CODE, EXIT));
    if (ft_strncmp(cmd[0], HERE_DOC_FILE, -1) != 0)
        execve(cmd[0], cmd, env);
    if (close(pipe[WRITE_END]) < 0)
        (pexit("heredoc: close", CLOSE_CODE, EXIT));
    clear(FREE_ALL);
    exit (7);
}

static char    *tmphd(char **env)
{
    pid_t pid;
    int pip[2];

    if (pipe(pip) < 0)
        return (pexit("pipe", PIPE_CODE, 0), NULL);
    pid = fork();
    if (pid < 0)
        return (pexit("fork", 1, 0), NULL);
    else if (pid == CHILD)
        tmphd_child(env, pip);
    return (tmphd_parent(pip));
}

int hd(char *delimit)
{
    int fd;
    char *tmpfile;

    tmpfile = tmphd(getcore()->env);
    if (!tmpfile)
        return (-1);
    tmpfile[ft_strlen(tmpfile) -1] = 0;
    hd_fork(tmpfile, delimit);
    fd = open(tmpfile, O_RDONLY);
    if (fd < 0)
        pexit("heredoc: tempfile", OPEN_CODE, 0);
    if (unlink(tmpfile) < 0)
        ft_putstr_fd(PRGM_NAME": heredoc: Warning: Failed to remove temporary file", 2);
    clear_1data(tmpfile);
    return (fd);
}
