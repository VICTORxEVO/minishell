



#include "minishell.h"

// return 1 on success, key only
//return 2 on success, (key, value)
//return 0 on failure

int ft_export_check(char *arg)
{
    size_t i;
    size_t c_count;

    i = 0;
    if (arg && (!ft_isalpha(arg[0]) || ft_isdigit(arg[0])) &&  arg[0]!= '_')
        return (0); 
    if (i > 0 && ft_strchr(arg, '='))
        return (2);
    return (1);
}

// return 1 on failure
int ft_add_export(t_cmd *cmd)
{

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

void free_env(t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        if (tmp->key)
            free(tmp->key);
        if (tmp->value)
            free(tmp->value);
        free(tmp);
        tmp = env->next;
    }
}

int ft_print_export()
{
    t_env *export;
    t_env *tmp;

    export = ft_copy_env();
    ft_sort_export(export);
    tmp = export;
    while (tmp)
    {
        if (tmp->value)
            printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
        else
            printf("declare -x %s\n", tmp->key); 
        tmp = tmp->next;
    }
    free_env(export);
    return (0);
}

int    ft_export(t_cmd *cmd)
{
    if (cmd->cmd[1])
        return (ft_add_export(cmd));
    else
        ft_print_export();
    return (0);
}

