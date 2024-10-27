



#include "minishell.h"


int ft_add_export(t_cmd *cmd)
{
    t_env *t_env;

    return (1);
}


int    ft_export(t_cmd *cmd)
{
    if (cmd->cmd[1])
        ft_add_export(cmd);
    else
        ft_print_export();
    return (1);
}

