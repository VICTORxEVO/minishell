#include "minishell.h"



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
    return (0);
}

int ft_print_export_error2(char *cmd)
{
    printf("Eureka: export: %s: not a valid identifier\n", cmd);
    return (0);
} 