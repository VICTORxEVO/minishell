#include "minishell.h"

static long long lexer_add_token(char type)
{
    t_all *core;
    t_lx *lexer;

    core = get_core();
    lexer = core->lexer;
    if (!lexer)
        lexer = galloc(sizeof(t_lx));
    else
    {
        while (lexer->next)
            lexer = lexer->next;
        lexer->next = galloc(sizeof(t_lx));
        lexer = lexer->next;
    }
    lexer->type = type;
    if (type == HERE_DOC || type == OUT_RDRT_APP)
        return (2); //skip the token by 2 in case of '<<' or '>>'
    return (1); //skip the token by 1 in case or '<' or '>'
    
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
        return (lexer_add_word(D_QUOTES));
    else if (line[0] == S_QUOTES)
        return (lexer_add_word(S_QUOTES));
    else
        return (lexer_add_word(WORD));
}
