





#include "minishell.h"


void    ft_remove_node(char *node)
{
    t_env *env;
    t_env *prev;

    env = get_core()->env_list;
    prev = NULL;
    while (env)
    {
        if (ft_strcmp(env->key, node) == 0)
        {
            if (prev == NULL)
                get_core()->env_list = env->next;
            else
                prev->next = env->next;
            free(env->key);
            free(env->value);
            free(env);
            break;
        }
        prev = env;
        env = env->next;
    }
}

int    ft_unset(t_cmd *cmd)
{
    t_env *env;

    env = get_core()->env_list;
    while (env && cmd->cmd[1])
    {
        if (ft_strcmp(env->key, cmd->cmd[1]) == 0)
            return (ft_remove_node(cmd->cmd[1]), 0);
        env = env->next;
    }
    return (1);
}

