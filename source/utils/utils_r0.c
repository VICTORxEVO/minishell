#include "minishell.h"

int     get_dollar(char *str, bool *flag)
{
    int i;

    i = -1;
    *flag = false;
    while(str[++i])
    {
        if (str[i] == S_QUOTES)
        {
            while (str[++i] != S_QUOTES)
                continue;
        }
        if (ft_isspace(str[i], NULL))
            *flag = true;
        if (str[i] == '$' && str[i + 1] && !ft_isspace(str[i + 1], NULL))
            return (i);
    }
    *flag = true;
    return (i);
}

bool    needexpand(char *str, t_lx *lexer)
{
    int i;

    i = -1;
    if (lexer && lexer->type == WORD)
    {
        if (lexer->prev && lexer->prev->type == HERE_DOC)
            return(false);
    }
    while (str && str[++i])
    {
        if (str[i] == '$' && str[i + 1] && !ft_isspace(str[i + 1], NULL))
            return (true);
    }
    return (false);
}

char    *strtkr_gen(char type)
{
    if (type == HERE_DOC)
        return (ft_strdup("<<"));
    else if (type == IN_RDRT)
        return (ft_strdup("<"));
    else if (type == OUT_RDRT_OW)
        return (ft_strdup(">"));
    else if (type == OUT_RDRT_APP)
        return (ft_strdup(">>"));
    else
        return (ft_strdup("|"));
}