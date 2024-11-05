#include "minishell.h"

void    addlexer(t_lx *node)
{
    t_lx *lexer;

    lexer = getcore()->lexer;
    if (!lexer)
        getcore()->lexer = node;
    else
    {
        while (lexer->next)
            lexer = lexer->next;
        lexer->next = node;
    }
}

void    addtolist(void *node, char *list_type)
{
    if (!ft_strncmp(list_type, "t_lx", -1))
        addlexer((t_lx *)node);
}