#include "minishell.h"

void exec_1cmd(t_cmd *cmd)
{
    if (is_builtin(cmd->cmd[0]))
    {
        
    }
    
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
        size = count_or_back(cmd_list, COUNT);
        cmd_list->cmd = galloc(sizeof(char *) * (size + 1));
        count_or_back(cmd_list, LOAD);
        cmd_list->cmd[size] = NULL;
        cmd_list = cmd_list->next;
    }
}

// exitcode formula (exit_code % 256 + 256) % 256
void    execution(void)
{
    load_cmd(getcore()->cmd);
    print_cmd();
    if (getcore()->cmd_count == 1)
        exec_1cmd(getcore()->cmd);
    else
        exec_ncmd(getcore()->cmd);
}
