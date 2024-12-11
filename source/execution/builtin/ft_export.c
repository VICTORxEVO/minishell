



#include "minishell.h"


static int ft_export_check(char *arg, bool *has_plus)
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
            *has_plus = 1;
            if (arg[i + 1] != '=')
                return (0);
        }
        else if (arg[i] == '=')
            return (1);
        else if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (0);
    }
    return (1);
}

static int parse_key_value(const char *arg, char **key, char **value) {
    char *equal_sign_pos;
    
    equal_sign_pos = ft_strchr(arg, '=');
    if (!equal_sign_pos)
    {
        *key = ft_strdup(arg);
        *value = NULL;
        return (*key) ? 1 : 0;
    }
    if (*(equal_sign_pos - 1) == '+')
        *key = ft_strndup(arg, equal_sign_pos - arg - 1);
    else
        *key = ft_strndup(arg , equal_sign_pos - arg);
    if (*(equal_sign_pos + 1) == '\0')
        *value = ft_strdup("");
    else if (equal_sign_pos)
        *value = ft_strdup(equal_sign_pos + 1);
    return (*key && *value) ? 1 : 0;
}

static int ft_add_export(char *arg, bool has_plus)
{
    char *key;
    char *value;

    parse_key_value(arg, &key, &value);
    if (value && has_plus)
        ft_setenv(key, value, 2); 
    else
        ft_setenv(key, value, 1); 
    return (1);
}

static void ft_print_export_error(char *var)
{
    pexit(ft_strjoin(ft_strjoin(ft_strjoin(": export: '", var), "'"), " not a valid identifier"), 1);
} 

int    ft_export(t_cmd *cmd)
{
    size_t i;
    bool has_plus;
    bool failed;

    i = 1;
    has_plus = 0;
    failed = 0;
    while (cmd->cmd[i])
    {
        if (ft_export_check(cmd->cmd[i], &has_plus))
            ft_add_export(cmd->cmd[i], has_plus);
        else
        {
            ft_print_export_error(cmd->cmd[i]);
            failed = 1;
        }
        i++;
        has_plus = 0;
    }
    if (!cmd->cmd[1])
        ft_print_export();
    return (failed);
}

