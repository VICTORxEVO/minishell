




#include "minishell.h"


int  ft_add_node(t_env *last_node,char *new_key, char *new_val)
{
    t_env *env;

    if (!last_node)
        return (0);
    env = galloc(sizeof(t_env));
    if (!env)
        return (0);
    env->key =  new_key;
    env->value = new_val; 
    env->next = NULL;
    if (last_node && last_node->next == NULL)
        last_node->next = env;
    else
        return (0);
    return (1); 
}

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

int ft_setenv(char *key, char *val, int overwrite) 
{
    t_env *env;
    t_env *prev;
    bool found;

    env = get_core()->env_list; 
    prev = NULL;
    found = false;
    while (env)
    {
        if (ft_strcmp(key, env->key) == 0)
        {
            if (overwrite && val) 
                env->value = val;
            found = true;
            break;
        }
        prev = env;
        env = env->next;
    }
    if (!found)
        if (ft_add_node(prev, key, val) == 0)
            return -1;
    return 1; 
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

