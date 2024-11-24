



#include "minishell.h"


static int ft_export_check(char *arg)
{
    int i;

    if (!arg || !arg[0])
        return (0);
    i = 0;

    if (!ft_isalpha(arg[i]) && arg[i] != '_')
        return (0);
    while (arg[++i])
    {
        if (arg[i] == '+')
        {
            if (arg[i + 1] != '=')
                return (0);
        }
        else if (arg[i] == '=')
            return (1);
        else if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (0);
    }
    return (0);
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

    env = getcore()->env_list;
    extract_key_value(arg, &key, &value);     
    ft_setenv(key, value, 1); 
    return (1);
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

