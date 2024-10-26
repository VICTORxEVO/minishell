#include "minishell.h"

static int get_var(char *var_str, int *index, char type)
{
    t_var *list;
    int len;

    len = 0;
    list = handle_list();
    if (type == '$')
    {
        list->content = ft_itoa(getpid());
        (*index) += 1;
        return (ft_strlen(list->content));
    }
    else if (type == '?')
    {
        list->content = ft_itoa(get_core()->exit_code);
        (*index) += 1;
        return (ft_strlen(list->content));
    }
    while(var_str[len] || ft_isspace(var_str[len], NULL) || var_str[len] == '$')
        len++;
    list->content = getenv(ft_substr(var_str, 0, len));
    *index += len;
    if (list->content)
        return(ft_strlen(list->content));
    //to do : handle start and end of the expanded varibale
    return (0);
}

static char *calc_max_len(char *str)
{
    char *dollar_str;
    t_ndx   index;
    bool    is_connect;

    is_connect = false;
    ft_bzero(&index, sizeof(t_ndx));
    index.d = get_dollar(str, &is_connect);
    index.l += index.d;
    while (index.d < ft_strlen(str))
    {
        index.i = index.d;
        if (str[index.i] == '$')
            index.l += get_var(&str[index.i], &index.i, str[index.i]);
        else if (str[index.i] == '?')
            index.l += get_var(&str[index.i], &index.i, str[index.i]);
        else //if its a normal string
            index.l += get_var(&str[index.i], &index.i, 'A');
        index.d += get_dollar(&str[index.d + 1], &is_connect);
        if (!is_connect)
            index.l += index.d - index.i;
    }
    printf("final len ->%d\n", index.l);
    return(galloc(sizeof(char) * (index.l + 1)));
}

static void     word_expander(t_lx *lx)
{
    char *new_str;
    char *str;
    t_var *list;
    int size;

    str = lx->content;
    new_str = calc_max_len(str);
    list = get_core()->var_list;
    while (list->next)
    {
        // to do 
        //1. copy string before content->start
        //2. copy content 
        //3. copy starting from  content->end to content->next->start
    }
    //copy the last content and the rest of string
}
static void split_content(char *lx_str, t_lx *lexer)
{
    (void)lx_str;
    (void)lexer;
}

void    expand_dollar(t_lx *lexer)
{
    while(lexer)
    {
        if (could_expand(lexer->content))
            word_expander(lexer);
        if (lexer->type == WORD)
            split_content(lexer->content, lexer);
        lexer = lexer->next;
    }
}