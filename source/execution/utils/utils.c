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

static char checkpathcase1(char *cmd, char *not_found, char *perm_denied, char **returnpath)
{
    char **path;
    int i;

    path = getcore()->path;
    i = -1;
    while (path[++i])
    {
        *returnpath = ft_strjoin(path[i], cmd);
        if (access(*returnpath, F_OK) == 0)
        {
            if (access(*returnpath, F_OK) == 0)
                return(0);
            return(pexit(perm_denied, PERM_DENIED_CODE, 0), 1);
        }
    }
    return(pexit(not_found, CMD_NOTFOUND_CODE, 0), 2);
}

static char checkpathcase0(char *path, char *not_found, char *perm_denied)
{

    if (path[0] == '/' || path[0] == '.' || !getcore()->path)
    {
        if (access(path, F_OK) < 0)
            return (pexit(not_found, CMD_NOTFOUND_CODE, 0), 1);
        if (access(path, F_OK) < 0)
            return (pexit(perm_denied, PERM_DENIED_CODE, 0), 2);
        return (0);
    }
    return (-1);
}

char    *getcmdpath(char *cmd)
{
    char res;
    char *not_found;
    char *perm_denied;
    char *fullpath;

    not_found = ft_strjoin(ft_strjoin(": ", cmd), CMD_NOTFOUND);
    perm_denied = ft_strjoin(ft_strjoin(": ", cmd), PERM_DENIED);
    res = checkpathcase0(cmd, not_found, perm_denied);
    if (res == 0)
        return(cmd);
    if (res > 0)
        return (NULL);
    if (res == -1)
    {
        res = checkpathcase1(cmd, not_found, perm_denied, &fullpath);
        if (res == 0)
            return(fullpath);
        if (res > 0)
            return (NULL);
    }
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
