#include "minishell.h"

static unsigned int return_or_fill(t_cmd *cmd, bool type)
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
        size = return_or_fill(cmd_list, COUNT);
        if (size == 0)
        {
            cmd_list = cmd_list->next;
            continue;
        }
        cmd_list->cmd = galloc(sizeof(char *) * (size + 1));
        return_or_fill(cmd_list, LOAD);
        cmd_list->cmd[size] = NULL;
        cmd_list = cmd_list->next;
    }
}