



#include "minishell.h"


int ft_add_export(t_cmd *cmd)
{
    t_env *t_env;
    char *val;
    char ** key_val;

    val = NULL;

    if (!ft_strchr(cmd->cmd[1], '='))
        ft_setenv(cmd->cmd[1], ft_strchr(,'=') + 1,1);
    
    t_env = ft_getenv(cmd->cmd[1]); 
    if (ft_strchr(cmd->cmd[1], '+'))


    val = ft_strjoin(key_val, ft_strchr(cmd->cmd[1] ,'=') + 1);
    ft_setenv(cmd->cmd[1],val,1);
    return (1);
}

t_env *copy_env()
{
    t_env *env;
    t_env *head;
    t_env *cpy;

    env = get_core()->env_list;
    if (!env)
        return (NULL);
    head = ft_copy_node(env);
    cpy = head;
    env = env->next;
    while (env)
    {
        cpy->next = ft_copy_node(env);
        cpy = cpy->next;
        env = env->next;
    }
    return (head);
}

void ft_print_export()
{
    t_env *export;

    export = copy_env();
    sort_env(export);

    while ()
}

int    ft_export(t_cmd *cmd)
{
    if (cmd->cmd[1])
        return (ft_add_export(cmd));
    else
        ft_print_export();
    return (0);
}

