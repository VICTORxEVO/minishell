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
    pexit(PTR_ERR, 101);
}