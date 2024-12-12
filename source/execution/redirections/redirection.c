#include "minishell.h"

int     redirection(char *filename, char mode, int oldfd)
{
    if (oldfd > 2)
        close (oldfd);
    if (mode == HERE_DOC)
        return (hd(filename));
    if (mode == HERE_DOC_FD)
        return (ft_atoi(filename));
    else if (mode == IN_RDRT)
        return (ifd(filename));
    else
        return (ofd(filename, mode));
}

static bool prepare_heredoc(t_cmd *cmd_list)
{
    int fd;
    t_lx *lexer;

    while (cmd_list)
    {
        lexer = cmd_list->scope;
        while (lexer)
        {
            if (lexer->type == HERE_DOC)
            {
                fd = redirection(lexer->next->content, lexer->type, 0);
                if (fd < 0)
                    return (false);
                clear_1data(lexer->next->content);
                lexer->type = HERE_DOC_FD;
                lexer->next->content = ft_itoa(fd);
            }
            lexer = lexer->next;
        }
        cmd_list = cmd_list->next;
    }
    return (true);
}

bool    prepare_ifof(t_cmd *cmd_list)
{
    t_lx *lexer;

    lexer = cmd_list->scope;
    if (cmd_list->unsed_fd > 2)
        close(cmd_list->unsed_fd);
    if (!prepare_heredoc(cmd_list))
        return (false);
    while (lexer)
    {   
        if (lexer->type == IN_RDRT || lexer->type == HERE_DOC_FD)
            cmd_list->ifd = redirection(lexer->next->content, lexer->type, cmd_list->ifd);
        else if (lexer->type == OUT_RDRT_APP || lexer->type == OUT_RDRT_OW)
            cmd_list->ofd = redirection(lexer->next->content, lexer->type, cmd_list->ofd);
        if (cmd_list->ofd < 0 || cmd_list->ifd < 0)
            return (close_allhd(lexer), false);
        lexer = lexer->next;
    }
    if (!duping(cmd_list->ifd, cmd_list->ofd))
        return(pexit("dup2", DUP2_CODE, 0), false);
    return(true);
}
