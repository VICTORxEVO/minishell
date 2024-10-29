



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


t_env *ft_copy_node(t_env *node)
{
    t_env *cpy_node;

    if (!node)
        return (NULL);
    cpy_node = (t_env *) malloc(sizeof(t_env*));
    cpy_node->key = node->key;
    cpy_node->value = node->value;
    cpy_node->next = NULL;

    return (cpy_node);
}

t_env *ft_copy_env()
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


void ft_swap_nodes(t_env *outer,  t_env *inner)
{
    char *key;
    char *val;

    key = inner->key;
    val = inner->value;
    inner->key =  outer->key;
    inner->value = outer->value;
    outer->key = key;
    outer->value = val;
}

t_env *ft_sort_export(t_env *export)
{
    t_env *outer;
    t_env *inner;

    outer = export;
    while (outer)
    {
        inner = outer->next;
        while (inner)
        {
            if (ft_strcmp(outer->key, inner->key) > 0)
                ft_swap_nodes(outer, inner);
            inner = inner->next;
        }
        outer = outer->next;
    }
    return (export);
}

void ft_print_export()
{
    t_env *export;

    export = ft_copy_env();
    ft_sort_export(export);

    // while ()
}

int    ft_export(t_cmd *cmd)
{
    if (cmd->cmd[1])
        return (ft_add_export(cmd));
    else
        ft_print_export();
    return (0);
}

