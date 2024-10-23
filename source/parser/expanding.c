#include "minishell.h"

static int get_var(char *dollar_str, char *str)
{
    t_var *list;

    if (str == dollar_str + 1 && !*str)
        return (1);
    list = handle_list();
    list->start_addr = dollar_str;
    list->end_addr = str;
    if (str == dollar_str + 1 && *str == '$')
    {
        list->content = ft_itoa(getpid());
        list->end_addr = str + 1;
        return (ft_strlen(list->content));
    }
    else if (str == dollar_str + 1 && *str == '?')
    {
        list->content = ft_itoa(get_core()->exit_code);
        list->end_addr = str + 1;
        return (ft_strlen(list->content));
    }
    list->content = getenv(ft_substr(dollar_str, 1,(str - dollar_str) - 1));
    return (ft_strlen(list->content));
}

static char *calc_max_len(char *str)
{
    char *dollar_str;
    int len;

    len = 0;
    dollar_str = get_dollar(str);
    len += dollar_str - str;
    while (dollar_str)
    {
        if ((*str == '$' && str > dollar_str + 1))
            len += dollar_str - str;
        str = dollar_str + 1;
        while (*str && !possible_expand(*str))
            str++;
        len += get_var(dollar_str, str);
        if (str == dollar_str + 1 && *str == '$')
            dollar_str += 1;
        dollar_str = get_dollar(dollar_str + 1);
    }
    dollar_str = get_end_addr(str);
    len += dollar_str - str;
    printf("final len is %d\n", len);
    return (galloc(sizeof(char) * len + 1));
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
    while (list)
    {
        size = list->start_addr - str;
        ft_memcpy(new_str + ft_strlen(new_str), str, size);
        ft_memcpy(new_str + ft_strlen(new_str), list->content, ft_strlen(list->content));
        str = (char *)list->end_addr;
        list = list->next;
    }
    ft_memcpy(new_str + ft_strlen(new_str), str, get_end_addr(str) - str);
    printf("new lexer str -> %s\\0\n", new_str);
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