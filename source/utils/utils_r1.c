#include "minishell.h"

t_var *handle_list(void)
{
    t_var *list;

    list = get_core()->var_list;
    if (!list)
    {
        list = galloc(sizeof(t_var));
        get_core()->var_list = list;
    }
    else
    {
        while(list->next)
            list = list->next;
        list->next = galloc(sizeof(t_var));
        list = list->next;
    }
    return (list);
}