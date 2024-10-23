





#include "minishell.h"


int    ft_unset(t_cmd *cmd)
{
    t_env *env;

    env = get_core()->env_list;
    while (env && cmd->cmd[1])
    {
        if (ft_strcmp(env->key, cmd->cmd[1]))
            return(ft_remove_node(env, cmd->cmd[1], 0));
        env = env->next;
    }
    return (1);
}

