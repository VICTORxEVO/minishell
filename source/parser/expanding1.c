#include "minishell.h"

int    get_var_special(int *index, char type)
{
    t_var *list;

    list = handle_list();
    (*index) += 1;
    list->end_ndx = (*index);
    list->start_ndx = (*index) - 2;
    if (type == '$')
        list->content = ft_itoa(getpid());
    else
        list->content = ft_itoa(getcore()->exit_code);
    return (ft_strlen(list->content));
}