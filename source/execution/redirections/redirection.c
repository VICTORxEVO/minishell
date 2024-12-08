#include "minishell.h"

int     redirection(char *filename, char mode, int oldfd)
{
    if (mode == HERE_DOC)
        return (hd(filename));
    else if (mode == IN_RDRT)
        return (ifd(filename));
    else
        return (ofd(filename, mode));
    if (oldfd > 2)
        close (oldfd);
}

bool    prepare_ifof(t_cmd *cmd_list)
{
    t_lx *lexer;

    lexer = cmd_list->scope;
    while (lexer)
    {
        if (lexer->type == IN_RDRT || lexer->type == HERE_DOC)
            cmd_list->ifd = redirection(lexer->next->content, lexer->type, cmd_list->ifd);
        else if (lexer->type == OUT_RDRT_APP || lexer->type == OUT_RDRT_OW)
            cmd_list->ofd = redirection(lexer->next->content, lexer->type, cmd_list->ofd);
        lexer = lexer->next;
    }
}