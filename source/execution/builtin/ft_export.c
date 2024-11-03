



#include "minishell.h"


// error to print =>  "bash_name": command (export): `user_input': not a valid identifier 
static int ft_export_check(char *arg)
{
    size_t i;
    bool plus;

    if (!arg)
        return (0);
    if ((arg[0] != '_') && !ft_isalpha(arg[0]))
        return (0);
    i = 1;
    plus = false;
    while (arg[i]) 
    {
        if ((arg[i] == '=') || (arg[i] == '+' && arg[i + 1] == '=') || arg[i] == '+' && plus)
        {
            i++;
            plus = true;
            continue;
        }
        if (!ft_isdigit(arg[i]) && !ft_isalpha(arg[i]) && !(arg[i] == '_'))
            return (0);
        i++; 
    }
    return (1);
}

static int extract_key_value(const char *arg, char **key, char **value) {
    char *equal_sign = ft_strchr(arg, '=');

    if (!equal_sign)
    {
        *key = ft_strdup(arg);
        *value = NULL;
        return (*key) ? 1 : 0;
    }
    *key = ft_strndup(arg, equal_sign - arg); 
    if (*(equal_sign + 1) == '\0')
        *value = ft_strdup("");
    else 
        *value = ft_strdup(equal_sign + 1);
    return (*key && *value) ? 1 : 0;
}

static int ft_add_export(char *arg)
{
    t_env *env;
    char *key;
    char *value;
    char *tmp;
    char *equal_sign;

    env = get_core()->env_list;
    extract_key_value(arg, key, value); 

    ft_setenv(key, value, 1); 
    return (1);
}

static int ft_print_export()
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

static void ft_print_export_error()
{
    printf("Eureka: export: `command': not a valid identifier\n");
} 

int    ft_export(t_cmd *cmd)
{
    size_t i;

    i = 1;
    while (cmd->cmd[i])
    {
        if (ft_export_check(cmd->cmd[i]))
            ft_add_export(cmd->cmd[i]);
        else
            ft_print_export_error();
    }
    if (!cmd->cmd[1])
        ft_print_export();
    return (0);
}

