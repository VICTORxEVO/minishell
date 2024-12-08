#include "minishell.h"

int exec_1cmd(t_cmd *cmd)
{
    int backup_fd[2];
    if (is_builtin(cmd->cmd[0]))
    {
        backup_fd[0] = dup(STDIN_FILENO);
        backup_fd[1] = dup(STDOUT_FILENO);
        prepare_ifof(getcore()->cmd);
        // to change to void
        exec_builtin(cmd->cmd);
        if (dup2(backup_fd[0], cmd->ifd) < 0 || dup2(backup_fd[1], cmd->ofd))
            return(pexit("dup2", DUP2_CODE), 1);
    }
    else
    {
        if (execvp(cmd->cmd[0], cmd->cmd) == -1)
        {
            //command not found 
            pexit(cmd->cmd[0], 127);
            return (1);
        }
        return (0);
    }
    return (1);
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
        cmd_list->cmd = galloc(sizeof(char *) * (size + 1));
        count_or_back(cmd_list, LOAD);
        cmd_list->cmd[size] = NULL;
        cmd_list = cmd_list->next;
    }
}

// exitcode formula (exit_code % 256 + 256) % 256 == exit_code & 0xFF
void    execution(void)
{
    prepare_ifof(getcore()->cmd);
    print_cmd();
    // if (getcore()->cmd_count == 1)
    //     exec_1cmd(getcore()->cmd);
    // else
    //     exec_ncmd(getcore()->cmd);
}
