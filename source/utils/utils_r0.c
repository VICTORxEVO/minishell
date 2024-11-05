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