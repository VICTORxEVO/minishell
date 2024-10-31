



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

int ft_add_export(t_cmd *cmd)
{
    t_env *env;
    char *key;
    char *value;
    char *tmp;
    char *equal_sign;

    env = get_core();
    equal_sign = ft_strchr(cmd->cmd[1], '=');
    if (equal_sign)
    {
        tmp = ft_strdup(cmd->cmd[1]); 
        *ft_strchr(tmp, '=') = 0;
        key = tmp;
        value = ft_strchr(cmd->cmd[1], '=') + 1;
        free(key);
        if (value)
            free(value);
    }
    else
    {
        key = cmd->cmd[1];
        value = 0;
    }
    ft_setenv(key, value, 1);
    return (1);
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
    if (cmd->cmd[1] && ft_export_check(cmd->cmd[1]))
        return (ft_add_export(cmd));
    else
        ft_print_export();
    return (0);
}

