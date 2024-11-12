



#include "minishell.h"


// return 0 in case of error
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

    env = get_core()->env_list;
    extract_key_value(arg, &key, &value);     
    ft_setenv(key, value, 1); 
    return (1);
}
int ft_print_export_error(char *cmd)
{
    printf("error exit %d\n", cmd);

    return (1);
}

int    ft_export(t_cmd *cmd)
{
    size_t i;
    int exit_status;

    i = 1;
    exit_status = 0;
    while (cmd->cmd[i])
    {
        if (ft_export_check(cmd->cmd[i]))
            ft_add_export(cmd->cmd[i]);
        else
            exit_status = ft_print_export_error(cmd->cmd[i]);
        i++;
    }
    if (!cmd->cmd[1])
        ft_print_export();
    return (exit_status);
}

