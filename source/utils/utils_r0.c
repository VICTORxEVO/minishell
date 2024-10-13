#include "minishell.h"

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