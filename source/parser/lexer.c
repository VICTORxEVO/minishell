#include "minishell.h"

static char *lexer_get_word(char *line, char type, long long *i)
{
     if (type == WORD_S_QUOTES)
     {
        while (line[++(*i)] != S_QUOTES)
            continue;
        return (ft_substr(line, 1, *i)); // start from index 1 to skip quote
     }
     else if (type == WORD_D_QUOTES)
     {
        while (line[++(*i)] != S_QUOTES)
            continue;
        return (ft_substr(line, 1, *i));
     }
     while (line[*i] && !ft_isspace(line[*i], NULL))
        ++(*i);
    return (ft_substr(line, 0, *i));
}

long long lexer_add_word(char type, char *line)
{
    t_lx *lexer;
    long long i;

    i = 0;
    lexer = get_core()->lexer;
    if (!lexer->next)
    {
        lexer->content = lexer_get_word(line, type, &i);
        lexer->type = type;
        return (i);
    }
    while (lexer->next)
        lexer = lexer->next;
    lexer->next = galloc(sizeof(t_lx));
    lexer->next->content = lexer_get_word(line, type, &i);
    lexer->next->type = type;
    return (i);
}
long long lexer_add_token(char type)
{
    t_lx *lexer;

    lexer = get_core()->lexer;
    if (!lexer->next)
        lexer->type = type;
    else
    {
        while (lexer->next)
            lexer = lexer->next;
        lexer->next = galloc(sizeof(t_lx));
        lexer->next->type = type;
    }
    if (type == HERE_DOC || type == OUT_RDRT_APP)
        return (2); //skip the token by 2 in case of '<<' or '>>'
    return (1); //skip the token by 1 in case or '<' or '>'
    
}


