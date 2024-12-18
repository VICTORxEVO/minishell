#include "minishell.h"

static int    *calc_points(char *str)
{
    t_ndx index;
    int *points;

    ft_bzero(&index, sizeof(t_ndx));
    index.l = ft_strlen(str);
    points = galloc(sizeof(int) * (index.l / 2 + 2));
    points[index.k++] = index.i;
    while (index.i < index.l)
    {
        if (wordstart(str[index.i], str[index.i + 1], index.i, index.l))
        {
            points[index.k++] = index.i + 1;
            index.j = index.i++;
            while (index.j >= 0 && ft_isspace(str[index.j], NULL))
                str[index.j--] = 0;
        }
        index.i += skipquotes(&str[index.i]);
    }
    points[index.k] = -1;
    return (points);
}


t_lx    *splitcontent(char *str)
{
    int *points;
    int i;
    t_lx *node;
    t_lx *head;

    head = NULL;
    points = calc_points(str);
    i = -1;
    while (points[++i] != -1)
    {
        node = galloc(sizeof(t_lx));
        node->content = ft_strdup(&str[points[i]]);
        node->type = WORD;
        if (!head)
            head = node;
        else
            addtolist(node, "t_lx", head);
    }
    return (clear_1data(points),clear_1data(str), head);
}

t_lx    *addnewlist(t_lx *new_list, t_lx *lexer, t_lx *prev_lx, t_lx *next_lx)
{
    t_lx *newlisttail;

    newlisttail = new_list;
    clear_1data(lexer);
    while(newlisttail->next)
        newlisttail = newlisttail->next;
    if (!prev_lx)
    {
        getcore()->lexer = new_list;
        newlisttail->next = next_lx;
        if (next_lx)
            next_lx->prev = newlisttail;
    }
    else
    {
        prev_lx->next = new_list;
        new_list->prev = prev_lx;
        newlisttail->next = next_lx;
        if (next_lx)
            next_lx->prev = newlisttail;
    }
    return (new_list);
}

int    get_var_special(int *index)
{
    t_var *list;

    list = handle_list();
    (*index) += 1;
    list->end_ndx = (*index);
    list->start_ndx = (*index) - 2;
    list->content = ft_itoa(getcore()->exit_code);
    return (ft_strlen(list->content));
}
