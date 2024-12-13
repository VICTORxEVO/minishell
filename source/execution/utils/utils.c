#include "minishell.h"

void close_allhd(t_lx *lexer)
{
    while (lexer)
    {
        if (lexer->type == HERE_DOC_FD)
            close(atoi(lexer->next->content));
        lexer = lexer->next;
    }
}

bool backup_fd(int *fd)
{
    if (fd[2] == 0)
    {
        fd[0] = dup(STDIN_FILENO);
        fd[1] = dup(STDOUT_FILENO);
        if (fd[0] < 0 || fd[1] < 0)
            return (pexit("dup", 1, 0), false);
    }
    else
    {
        if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
            return(pexit("dup2", DUP2_CODE, 0), false);
        if (close(fd[0]) < 0 || close(fd[1]) < 0)
            return(pexit("close", CLOSE_CODE, 0), false);
    }
    return(true);
}

static bool checkpath(char *path)
{
    if (access(path, F_OK) == 0)
    {
        if (access(path, X_OK) < 0)
            pexit(ft_strjoin(ft_strjoin(": ", path), PERM_DENIED), PERM_DENIED_CODE, 0);
        return (0);
    }
    return (1);
}

char    *getcmdpath(char *cmd)
{
    char *fullpath;
    int i;

    if (cmd[0] == '/' || cmd[0] == '.' || !getcore()->path)
    {
        if (checkpath(cmd) == 0)
            return (cmd);
    }
    else
    {
        i = -1;
        while (getcore()->path && getcore()->path[++i])
        {
            fullpath = ft_strjoin(getcore()->path[i], cmd);
            if (checkpath(fullpath) == 0)
                return (fullpath);
        }
    }
    pexit(ft_strjoin(ft_strjoin(": ", cmd), CMD_NOTFOUND), CMD_NOT_FOUND_CODE, EXIT);
    return (NULL);
}

pid_t   forker(void (*child_fn)(void *), void *child_arg,
                    void (*parent_fn)(void *, pid_t), void *parent_arg)
{
    pid_t   pid;

    if (!child_fn || !parent_fn)
        return(pexit(":forker: "FATAL_ERR"function pointer is NULL !", 1, EXIT), -1);
    pid = fork();
    if (pid == -1)
    {
        pexit("fork", FORK_CODE, EXIT);
        return (-1);
    }
    if (pid == 0)
        (child_fn(child_arg), exit(211));
    if (parent_fn)
        parent_fn(parent_arg, pid);
    return (pid);
}
