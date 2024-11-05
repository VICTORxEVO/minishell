#include "minishell.h"

static char *lexer_get_word(char *line, char type, long long *i)
{
    char quote;

    while (line[*i] && !ft_isspace(line[*i], NULL) && !is_token(line[*i]))
     {
        if (line[*i] == S_QUOTES || line[*i] == D_QUOTES)
        {
            quote = line[*i];
            while (quote != line[++(*i)])
                continue;
        }
        if (!line[*i] || ft_isspace(line[*i], NULL) || is_token(line[*i]))
            break;
        (*i)++;
     }
    return (ft_substr(line, 0, *i));
}

long long lexer_add_word(char type, char *line)
{
    t_lx *lexer;
    long long i;

    i = 0;
    lexer = galloc(sizeof(t_lx));
    lexer->type = WORD;
    lexer->content = lexer_get_word(line, WORD, &i);
    addtolist(lexer, "t_lx");
    return (i);
}
long long lexer_add_token(char type)
{
    t_lx *lexer;

    lexer = galloc(sizeof(t_lx));
    lexer->type = type;
    lexer->content = strtkr_gen(type);
    addtolist(lexer, "t_lx");
    if (type == HERE_DOC || type == OUT_RDRT_APP)
        return (2); //skip the token by 2 in case of '<<' or '>>'
    return (1); //skip the token by 1 in case or '<' or '>'
    
}
