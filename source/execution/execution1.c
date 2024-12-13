#include "minishell.h"

void    wait_childs(pid_t *pid)
{
    int i;
    int status;

    i = -1;
    while(++i < (int)getcore()->cmd_count)
        waitpid(pid[i], &status, 0);
    getcore()->exit_code = WEXITSTATUS(status);
}

void    exec_cmdparent(void *data, pid_t pid)
{
    int status;
    int *i;
    int signal ;

    signal = 0;
    i = (int *)data;
    if (i)
    {
        getcore()->pids[*i] = pid;
        if (*i + 1 == (int)getcore()->cmd_count)
            wait_childs(getcore()->pids);
        return ;
    }
        wait(&status);
        if (WIFSIGNALED(status))
        {
            signal = WTERMSIG(status) + 128;
            if (WTERMSIG(status) == SIGSEGV)
                ft_putstr_fd("Segmentation fault (core dumped)\n", 2);
        }
        getcore()->exit_code = WEXITSTATUS(status) + signal;
}

void    exec_cmdchild(void *data)
{
    t_cmd *cmd;
    char *cmdpath;
    int exitcode;

    exitcode = 0;
    cmd = (t_cmd *)data;
    if (!prepare_ifof(cmd))
        (clear(FREE_ALL), exit(getcore()->exit_code));
    if (cmd->cmd && !is_builtin(cmd->cmd[0]))
    {
        cmdpath = getcmdpath(cmd->cmd[0]);
        execve(cmdpath, cmd->cmd, getcore()->env);
        (close(cmd->ifd), close(cmd->ofd));
        pexit("execve", 1, EXIT);
    }
    exitcode = exec_builtin(cmd);
    (close(cmd->ifd), close(cmd->ofd));
    (clear(FREE_ALL), exit(exitcode));
}
