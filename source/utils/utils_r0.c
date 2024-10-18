#include "minishell.h"

char *get_dollar(char *str)
{
    while(*str)
    {
        if (*str == '$')
            return (str);
        str++;
    }
    return (NULL);
}


bool    is_pipe_err(t_lx *lx, t_lx *next_lx)
{
    if (lx->type == PIPE && (!next_lx || next_lx->type == PIPE))
        return (true);
    return (false);
}

bool    is_token_err(t_lx *lx, t_lx *next_lx)
{
    if (lx->type != PIPE && is_token(lx->type))
    {
        if (!next_lx || is_token(next_lx->type))
            return(true);
    }
    return(false);
}

bool    could_expand(char *str)
{
    int i;

    i = -1;
    while (str[++i])
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