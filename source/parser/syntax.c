#include "minishell.h"


bool    check_quotes(char *line)
{
    long long i;
    char quote;

    i = -1;
    while (line[++i])
    {
        if (line[i] == S_QUOTES || line[i] == D_QUOTES)
        {
            quote = line[i++];
            while (line[i] && line[i] != quote)
                i++;
            if (line[i] != quote)
                    return (pexit(DQ_ERR, 1, 0), false);
        }
    }
    return (true);
}
