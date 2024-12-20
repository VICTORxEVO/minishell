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
            printf("%s=\"%s\"\n", tmp->key, tmp->value);
        else
            printf("%s\n", tmp->key); 
        tmp = tmp->next;
    }
    return (0);
}
