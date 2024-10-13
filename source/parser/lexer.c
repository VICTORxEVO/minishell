#include "minishell.h"

static long long lexer_add_token(char type)
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

static long long lexer_add_word(char type, char *line)
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

long long lexer_add(char *line)
{
    if (line[0] == '<' && line[1] == '<')
        return (lexer_add_token(HERE_DOC));
    else if (line[0] == '>' && line[1] == '>')
        return (lexer_add_token(OUT_RDRT_APP));
    else if (line[0] == '<')
        return (lexer_add_token(IN_RDRT));
    else if (line[0] == '>')
        return (lexer_add_token(OUT_RDRT_OW));
    else if (line[0] == '|')
        return (lexer_add_token(PIPE));
    else if (line[0] == D_QUOTES)
        return (lexer_add_word(WORD_D_QUOTES, line));
    else if (line[0] == S_QUOTES)
        return (lexer_add_word(WORD_S_QUOTES, line));
    else
        return (lexer_add_word(WORD, line));
}
