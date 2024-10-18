#include "minishell.h"


void    check_quotes(char *line)
{
    long long i;

    i = -1;
    while (line[++i])
    {
        if (line[i] == S_QUOTES)
        {
            while (line[++i] && line[i] != S_QUOTES)
                continue;
            if (!line[i])
                pexit(SQ_ERR, 1);
        }
        else if (line[i] == D_QUOTES)
        {
            while (line[++i] && line[i] != D_QUOTES)
                continue;
            if (!line[i])
                pexit(DQ_ERR, 1);
        }
    }
}

void    check_syntax(t_lx *lexer)
{
    while (lexer)
    {
        if (is_token_err(lexer, lexer->next))
            pexit(ft_strjoin(ft_strjoin(TOKEN_ERR, lexer->content), "'"), 1);
        else if (is_pipe_err(lexer, lexer->next))
            pexit(PIPE_ERR, 1);
        lexer = lexer->next;
    }
}