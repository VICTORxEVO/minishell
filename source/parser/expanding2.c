#include "minishell.h"

int skipquotes(char *str)
{
    char quote;
    int i;

    i = 0;
    if (str[i] == S_QUOTES || str[i] == D_QUOTES)
    {
        quote = str[i++];
        while (str[i] != quote)
            i++;
        return (i + 1);
    }
    return (1);
}


bool wordstart(char a, char b, int i, int maxlen)
{
    if (ft_isspace(a, NULL))
    {
        if (i + 1 < maxlen && !ft_isspace(b, NULL))
            return (true);
    }
    return (false);
}