#include "minishell.h"

char    *heredoc_case(t_lx *lexer)
{
    char *new_content;
    int content_len;

    while (lexer)
    {
        if (lexer->type == HERE_DOC)
        {
            content_len = ft_strlen(lexer->next->content);
            new_content = galloc(sizeof(char) * (content_len + 3));
            new_content[0] = S_QUOTES;
            ft_strlcpy(&new_content[1], lexer->next->content, content_len + 1);
            new_content[content_len + 2] = S_QUOTES;
        }
        lexer = lexer->next;
    }
}
