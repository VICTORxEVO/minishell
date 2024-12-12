#include "minishell.h"

void    exec_1cmdparent(void *data, pid_t pid)
{
    int status;
    int *i;

    i = (int *)data;
    getcore()->pids[*i] = pid;
    waitpid(pid, &status, 0);
    getcore()->exit_code = WEXITSTATUS(status);
}

void    exec_1cmdchild(void *data)
{
    t_cmd *cmd;
    char *cmdpath;

    cmd = (t_cmd *)data;
    if (!prepare_ifof(cmd))
        (clear(FREE_ALL), exit(getcore()->exit_code));
    if (cmd->cmd)
    {
        cmdpath = getcmdpath(cmd->cmd[0]);
        execve(cmdpath, cmd->cmd, getcore()->env);
        pexit("execve", 1, EXIT);
    }
    getcore()->exit_code = 0;
    clear(FREE_ALL);
}