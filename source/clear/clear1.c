#include "minishell.h"

void clear_1data(void *data)
{
    t_gc *list;

    list = getcore()->gc;
    while(list)
    {
        if (list->data == data)
        {
            safe_free((void **)&list->data);
            return ;
        }
        list = list->next;
    }
    return (pexit(PTR_ERR, 101), clear(FREE_ALL), exit(101), (void)0);
}

static  void clear_t_vat(t_var *list)
{
    t_var *tmp;

    while(list)
    {
        tmp = list->next;
        clear_1data(list);
        list = tmp;
    }
    getcore()->var_list = NULL;
}

void    clear_1list(void *list, char *list_type)
{
    if (!ft_strncmp(list_type, "t_var", -1))
        clear_t_vat((t_var *)list);
}
