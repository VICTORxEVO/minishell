#include "minishell.h"

void    exec_1cmdparent(void *data, pid_t pid)
{
    int status;

    (void)data;
    (void)pid;
    wait(&status);
    getcore()->exit_code = WEXITSTATUS(status);
}

void    exec_1cmdchild(void *data)
{
    t_cmd *cmd;
    char *cmdpath;

    cmd = (t_cmd *)data;
    if (!prepare_ifof(cmd))
        clear(FREE_ALL);
    cmdpath = getcmdpath(cmd->cmd[0]);
    execve(cmdpath, cmd->cmd, getcore()->env);
}