#include "minishell.h"

static int get_var(char *dollar_str, char *str)
{
    t_var *list;

    list = handle_list();
    if (str == dollar_str + 1 && *str == '$')
    {
        list->content = ft_itoa(getpid());
        return (ft_strlen(list->content));
    }
    else
    {
        list->content = getenv(ft_substr(dollar_str, 1,(str - dollar_str) - 1));
        if (list->content)
            return (ft_strlen(list->content));
        return (0);
    }
}

static char *calc_max_len(char *str)
{
    char *new_str;
    int len;

    len = 0;
    new_str = get_dollar(str);
    len += new_str - str;
    while (new_str)
    {
        if (*str != '$')
            len += new_str - str;
        str = new_str + 1;
        while (*str && *str != '$' && !ft_isspace(*str, NULL))
            str++;
        if (str == new_str + 1 && (!*str || ft_isspace(*str, NULL)))
            len += 1;
        else
            len += get_var(new_str, str);
        if (*str == '$')
            new_str += 1;
        new_str = get_dollar(new_str + 1);
    }
    printf("final len is %d\n", len);
    return (galloc(sizeof(char) * len + 1));
}


static void    dq_word_expander(t_lx *lx)
{
    char *new_str;

    new_str = calc_max_len(lx->content);
    (void)new_str;
}

static void     word_expander(t_lx *lx)
{
    char *new_str;

    new_str = calc_max_len(lx->content);
    (void)new_str;
}

void    expand_dollar(t_lx *lexer)
{
    while(lexer)
    {
        if (lexer->type == WORD && could_expand(lexer->content))
            word_expander(lexer);
        else if (lexer->type == WORD_D_QUOTES && could_expand(lexer->content))
            dq_word_expander(lexer);
        lexer = lexer->next;
    }
}