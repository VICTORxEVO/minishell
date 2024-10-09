#include "minishell.h"

void    load_elements(char *line)
{
    long long i;

    i = -1;
    while (line[++i])
    {
        while (line[i] && ft_isspace(line[i], NULL))
            i++;
        if (ft_istoken(line[i]))
            i += lexer_add(line + (i + 1));
        else if (line[i] == D_QUOTES)
            i += lexer_add(line + (i + 1));
        else if (line[i] == S_QUOTES)
            i += lexer_add(line + (i + 1));
        else
            i += lexer_add(line + (i + 1));
    }
}

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
