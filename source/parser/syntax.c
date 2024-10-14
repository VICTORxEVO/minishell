#include "minishell.h"


void    check_quotes(char *line)
{
    long long i;

    i = -1;
    while (line[++i])
    {
        if (line[i] == S_QUOTES)
        {
            while (line[i] && line[i] != S_QUOTES)
                i++;
            if (!line[i])
                pexit(SQ_ERR, 1);
        }
        else if (line[i] == D_QUOTES)
        {
            while (line[i] && line[i] != D_QUOTES)
                i++;
            if (!line[i])
                pexit(DQ_ERR, 1);
        }
    }
}


void    check_syntax(t_lx *lexer)
{
    
}