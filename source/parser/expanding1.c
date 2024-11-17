#include "minishell.h"

t_lx    *splitcontent(char *str)
{
    (void)str;
    return ((t_lx *)0);
}

t_lx    *addnewlist(t_lx *new_list, t_lx *lexer, t_lx *prev_lx, t_lx *next_lx)
{
    t_lx *newlisttail;

    newlisttail = new_list;
    while(newlisttail->next)
        newlisttail = newlisttail->next;
    if (!prev_lx)
    {
        getcore()->lexer = new_list;
        newlisttail->next = next_lx;
        next_lx->prev = newlisttail;
    }
    else
    {
        clear_1data(lexer->content);
        clear_1data(lexer);
        prev_lx->next = new_list;
        new_list->prev = prev_lx;
        newlisttail->next = next_lx;
        next_lx->prev = newlisttail;
    }
    return (new_list);
}

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