#include "minishell.h"

void exec_1cmd(t_cmd *cmd)
{
    int bfd[3];

    bfd[2] = 0;
    if (cmd->cmd && is_builtin(cmd->cmd[0]))
    {
        if (backup_fd(bfd) == 1 || prepare_ifof(cmd) == 1)
            return ;
        getcore()->exit_code = exec_builtin(cmd);
        bfd[2] = -1;
        backup_fd(bfd);
    }
    else
        forker(exec_cmdchild, cmd, exec_cmdparent, NULL);
}

void  exec_ncmd(t_cmd *cmd)
{
    unsigned int i;
    int pip[2];

    if (gen_newpip(pip, cmd) == 1)
        return ;
    i = 0;
    while (i < __INT32_MAX__)
    {
        if (forker(exec_cmdchild, cmd, exec_cmdparent, &i) < 0)
            return (pexit("fork", FORK_CODE, 0), (void)0);
        if (cmd->ifd > 2)
            close(cmd->ifd);
        cmd = cmd->next;
        if (!cmd)
            return ;
        close(pip[WRITE_END]);
        cmd->ifd = pip[READ_END];
        if (i++ + 2 < getcore()->cmd_count)
        {
            if (gen_newpip(pip, cmd) == 1)
                return ;
        }
    }
}   

void    execution(void)
{
    if (getcore()->cmd_count == 1)
        exec_1cmd(getcore()->cmd);
    else
        exec_ncmd(getcore()->cmd);
    if (getcore()->hd_mode == true)
        close_allhd(getcore()->lexer);
}
