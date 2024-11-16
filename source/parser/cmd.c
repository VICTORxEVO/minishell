#include "minishell.h"

static int calclen(char *str, int *quotes)
{
    t_ndx index;
    char quote;

    ft_bzero(&index, sizeof(t_ndx));
    index.l = ft_strlen(str);
    while (str[index.i])
    {
        if (str[index.i] == S_QUOTES || str[index.i] == D_QUOTES)
        {
            quotes[index.j++] = index.i;
            quote = str[index.i++];
            while (str[index.i] != quote)
                index.i++;
            quotes[index.j++] = index.i;
        }
        index.i++;
    }
    quotes[index.j] = -3070;
    return (index.l - index.j);
}

static char *getnewstr(char *str)
{
    t_ndx index;
    int quotes[8192];
    char *newstr;

    ft_bzero(&index, sizeof(t_ndx));
    index.l = calclen(str, quotes);
    newstr = galloc(sizeof(char) * (index.l + 1));
    while (str[index.i])
    {
        if (index.i == quotes[index.m])
        {
            index.m++;
            index.i++;
            continue;
        }
        newstr[index.t++] = str[index.i++];
    }
    return (newstr);
}

static bool havequotes(t_lx *lexer)
{
    if (lexer->type = WORD)
    {
        if (ft_strchr(lexer->content, S_QUOTES))
            return (true);
        else if (ft_strchr(lexer->content, D_QUOTES))
            return (true);
    }
    return (false);
}

void    final_touch(t_lx *lexer)
{
    char *new_str;

    while (lexer)
    {
        if (havequotes(lexer))
        {
            new_str = getnewstr(lexer->content);
            clear_1data(lexer->content);
            lexer->content = new_str;
        }
    }
}

void    load_cmd_list(t_all *core)
{
    t_lx *lexer;
    t_cmd   *cmd;

    lexer = core->lexer;
    core->cmd_count = core->pipe_count + 1;
    // to add scopes ....
}
