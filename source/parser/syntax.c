#include "minishell.h"

void    load_elements(char *line)
{
    long long i;

    i = 0;
    while (line[i])
    {
        while (line[i] && ft_isspace(line[i], NULL))
            i++;
        if (line[i] == '<' && line[i + 1] == '<')
            i += lexer_add_token(HERE_DOC);
        else if (line[i] == '>' && line[i + 1] == '>')
            i += lexer_add_token(OUT_RDRT_APP);
        else if (line[i] == '<')
            i += lexer_add_token(IN_RDRT);
        else if (line[i] == '>')
            i += lexer_add_token(OUT_RDRT_OW);
        else if (line[i] == '|')
            i += lexer_add_token(PIPE);
        else if (line[i] == D_QUOTES)
            i += lexer_add_word(WORD_D_QUOTES, line);
        else if (line[i] == S_QUOTES)
            i += lexer_add_word(WORD_S_QUOTES, line);
        else
            i += lexer_add_word(WORD, line);
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
