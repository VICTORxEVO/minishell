#include "minishell.h"

static  bool checklastnode(t_lx *lastnode)
{
    if (istoken(lastnode->type, ALL_TKN))
    {
        pexit(ft_strjoin(ft_strjoin(TOKEN_ERR, lastnode->content), "'"), 1, 0);
        return (false);
    }
    return(true);
}
static char *lexer_get_word(char *line, long long *i)
{
    char quote;

    while (line[*i] && !ft_isspace(line[*i], NULL) && !istoken(line[*i], ALL_TKN))
     {
        if (line[*i] == S_QUOTES || line[*i] == D_QUOTES)
        {
            quote = line[*i];
            while (quote != line[++(*i)])
                continue;
        }
        if (!line[*i] || ft_isspace(line[*i], NULL) || istoken(line[*i], ALL_TKN))
            break;
        (*i)++;
     }
    return (ft_substr(line, 0, *i));
}

static long long lexer_add_word(char *line)
{
    t_lx *lexer;
    long long i;

    i = 0;
    lexer = galloc(sizeof(t_lx));
    lexer->type = WORD;
    lexer->content = lexer_get_word(line, &i);
    addtolist(lexer, "t_lx", NULL);
    return (i);
}
static long long lexer_add_token(char type)
{
    t_lx *lexer;
    t_lx *prev_nd;

    lexer = galloc(sizeof(t_lx));
    lexer->type = type;
    lexer->content = strtkr_gen(type);
    prev_nd = (t_lx *)getlastnode(getcore()->lexer, "t_lx");
    if (!prev_nd && lexer->type == PIPE)
        pexit(ft_strjoin(ft_strjoin(TOKEN_ERR, "|"), "'"), 1, 0);
    else if (prev_nd && istoken(prev_nd->type, NON_PIPE))
        pexit(ft_strjoin(ft_strjoin(TOKEN_ERR, prev_nd->content), "'"), 1, 0);
    addtolist(lexer, "t_lx", NULL);
    if (type == PIPE)
        getcore()->pipe_count++;
    if (type == HERE_DOC || type == OUT_RDRT_APP)
        return (2); //skip the token by 2 in case of '<<' or '>>'
    return (1); //skip the token by 1 in case or '<' or '>'
}

bool    lexing(char *line)
{
    long long i;

    i = 0;
    while (line[i])
    {
        while (line[i] && ft_isspace(line[i], NULL))
            i++;
        if (!ft_strncmp(&line[i], "<<", 2))
            i += lexer_add_token(HERE_DOC);
        else if (!ft_strncmp(&line[i], ">>", 2))
            i += lexer_add_token(OUT_RDRT_APP);
        else if (!ft_strncmp(&line[i], "<", 1))
            i += lexer_add_token(IN_RDRT);
        else if (!ft_strncmp(&line[i], ">", 1))
            i += lexer_add_token(OUT_RDRT_OW);
        else if (!ft_strncmp(&line[i], "|", 1))
            i += lexer_add_token(PIPE);
        else if (line[i])
            i += lexer_add_word(line + i);
        if (getcore()->error_flag)
            return (false);
    }
    if (!checklastnode((t_lx *)getlastnode(getcore()->lexer, "t_lx")))
        return(false);
    return (true);
}
