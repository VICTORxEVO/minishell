#include "minishell.h"

static int get_var(char *var_str, int *index)
{
    t_var *list;
    int len;

    len = 0;
    list = handle_list();
    while(var_str[len] && (!ft_isspace(var_str[len], NULL) && var_str[len] != '$'))
        len++;
    list->content = getenv(ft_substr(var_str, 0, len));
    list->start_ndx = (*index) - 1;
    *index += len;
    list->end_ndx = (*index);
    if (list->content)
        return(ft_strlen(list->content));
    return (0);
}

static char *create_str(char *str)
{
    t_ndx   index;
    bool    flag;

    flag = false;
    ft_bzero(&index, sizeof(t_ndx));
    index.d = get_dollar(str, &flag);
    index.l += index.d;
    while ((size_t)index.d < ft_strlen(str))
    {
        index.i = index.d + 1;
        if (str[index.i] == '$' || str[index.i] == '?')
            index.l += get_var_special(&index.i, str[index.i]);
        else //if its a normal string
            index.l += get_var(&str[index.i], &index.i);
        index.d += get_dollar(&str[index.d + 2], &flag) + 2;
        if (flag)
            index.l += index.d - index.i;
    }
    return(galloc(sizeof(char) * (index.l + 1)));
}

static void     word_expander(t_lx *lx)
{
    char *new_str;
    t_var *list;
    int size;

    new_str = create_str(lx->content);
    list = getcore()->var_list;
    size = list->start_ndx;
    strocpy(&new_str[ft_strlen(new_str)], lx->content, size);
    while (list->next)
    {
        strocpy(&new_str[ft_strlen(new_str)], list->content, -1);
        size = list->next->start_ndx - list->end_ndx;
        strocpy(&new_str[ft_strlen(new_str)], &lx->content[list->end_ndx], size);
        list = list->next;
    }
    strocpy(&new_str[ft_strlen(new_str)], list->content, -1);
    strocpy(&new_str[ft_strlen(new_str)], &lx->content[list->end_ndx], -1);
    //copy the last content and the rest of string
}
static void split_content(char *lx_str, t_lx *lexer)
{
    t_lx *next_node;
    char *string;

    next_node = lexer->next;
    string = strtok(lexer->content, SPACE);
    while (string)
    {
        lexer->next = galloc(sizeof(t_lx));
        lexer = lexer->next;
        lexer->content = string;
        string = strtok(lexer->content, SPACE);
    }
    lexer->next = next_node;
}

void    expand_dollar(t_lx *lexer)
{
    while(lexer)
    {
        if (could_expand(lexer->content))
            word_expander(lexer);
        if (lexer->type == WORD && is_str_havespace(lexer->content))
            split_content(lexer->content, lexer);
        lexer = lexer->next;
    }
}