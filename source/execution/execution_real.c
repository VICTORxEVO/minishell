#include "minishell.h"

int exec_1cmd(t_cmd *cmd)
{
    int bfd[3];

    bfd[2] = 0;
    if (cmd->cmd && is_builtin(cmd->cmd[0]))
    {
        if (!backup_fd(bfd) || !prepare_ifof(cmd))
            return (false);
        // to change to void
        exec_builtin(cmd);
        bfd[2] = -1;
        // backup_fd(bfd);
    }
    else
    {
        if (forker(exec_1cmdchild, cmd, exec_1cmdparent, NULL) < 0)
            return (false);
    }
    return (true);
}

int  exec_ncmd(t_cmd *cmd)
{


    return (0);
}   

unsigned int count_or_back(t_cmd *cmd, bool type)
{
    unsigned int i;
    t_lx *lx;

    lx = cmd->scope;
    i = 0;
    while (lx)
    {
        if (lx->type == WORD && (!lx->prev || (lx->prev && !istoken(lx->prev->type, NON_PIPE))))
        {
            if (type == COUNT)
                i++;
            else
                cmd->cmd[i++] = lx->content;
        }
        lx = lx->next;
    }
    return (i);
}

void load_cmd(t_cmd *cmd_list)
{
    unsigned int size;

    while (cmd_list)
    {
        cmd_list->ofd = 1;
        size = count_or_back(cmd_list, COUNT);
        if (size == 0)
        {
            cmd_list = cmd_list->next;
            continue;
        }
        cmd_list->cmd = galloc(sizeof(char *) * (size + 1));
        count_or_back(cmd_list, LOAD);
        cmd_list->cmd[size] = NULL;
        cmd_list = cmd_list->next;
    }
}

// exitcode formula (exit_code % 256 + 256) % 256 == exit_code & 0xFF
void    execution(void)
{
    print_cmd();
    if (getcore()->cmd_count == 1)
        exec_1cmd(getcore()->cmd);
    // else
    //     exec_ncmd(getcore()->cmd);
}
