#include "minishell.h"

static int get_var(char *var_str, int *index)
{
    t_var *list;
    int len;

    len = 0;
    list = handle_list();
    while(var_str[len] && ft_isalnum(var_str[len]))
        len++;
    list->content = ft_getenv(ft_substr(var_str, 0, len));
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

char    *expand_dollar(char *line)
{
    char *expline;
    t_var *list;
    int size;

    expline = create_str(line);
    list = getcore()->var_list;
    size = list->start_ndx;
    strocpy(&expline[ft_strlen(expline)], line, size);
    while (list->next)
    {
        strocpy(&expline[ft_strlen(expline)], list->content, -1);
        size = list->next->start_ndx - list->end_ndx;
        strocpy(&expline[ft_strlen(expline)], &line[list->end_ndx], size);
        list = list->next;
    }
    strocpy(&expline[ft_strlen(expline)], list->content, -1);
    strocpy(&expline[ft_strlen(expline)], &line[list->end_ndx], -1);
    clear_1list(list, "t_var");
    return (expline);
}

void    expanding(t_lx *lexer)
{
    char *new_content;
    t_lx *new_list;

    while (lexer)
    {
        if (needexpand(lexer->content, lexer))
        {
            new_content = expand_dollar(lexer->content);
            lexer->original_content = lexer->content;
            lexer->content = ft_strtrim(new_content, IS_SPACE); 
            clear_1data(new_content);
        }
        lexer = lexer->next;
    }
    lexer = getlastnode(getcore()->lexer, "t_lx");
    while (lexer)
    {
        if (needspliting(lexer, lexer->prev))
        {
            new_list = splitcontent(lexer->content);
            lexer = addnewlist(new_list, lexer, lexer->prev, lexer->next);
        }
        lexer = lexer->prev;
    }
}
