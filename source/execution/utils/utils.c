#include "minishell.h"

bool backup_fd(int *fd)
{
    if (fd[2] == 0)
    {
        fd[0] = dup(STDIN_FILENO);
        fd[1] = dup(STDOUT_FILENO);
        if (fd[0] < 0 || fd[1] < 0)
            return (pexit("dup", 1), false);
    }
    else
    {
        if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
            return(pexit("dup2", DUP2_CODE), false);
    }
    return(true);
}



char *getpath(char *cmd)
{
    char *paths;
    char *fullpath;
    int i;

    paths = getcore()->path;
    if (cmd[0] == '/' || cmd[0] == '.' || !paths)
        return(cmd);
    i = -1;
    while (paths[++i])
    {
        fullpath = ft_strjoin(paths, cmd);
        if (access(fullpath, X_OK) == 0)
            return(clear_1data(cmd), fullpath);
    }
    return(NULL);
}

pid_t   forker(void (*child_fn)(void *), void *child_arg,
                    void (*parent_fn)(void *), void *parent_arg)
{
    pid_t   pid;

    if (!child_fn || !parent_fn)
        return(pexit(":forker: "FATAL_ERR"function pointer is NULL !", 1), -1);
    pid = fork();
    if (pid == -1)
    {
        pexit("fork", FORK_CODE);
        return (-1);
    }
    if (pid == 0)
        (child_fn(child_arg), exit(211));
    parent_fn(parent_arg);
    return (pid);
}
