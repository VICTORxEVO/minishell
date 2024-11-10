#include "minishell.h"

static void addifof(t_cmd *cmd, t_lx *lexer, char redirect_type)
{
    t_file *node;
    t_file *tmp;

    node = galloc(sizeof(t_file));
    node->content = lexer->content;
    node->mode = redirect_type;
    tmp = cmd->infile;
    if (redirect_type == IN_RDRT)
        cmd->infile = node;  
}

static bool isifof(t_lx *lexer, t_lx *prev_lexer)
{
    if (lexer->type == WORD && prev_lexer)
    {
        if (istoken(prev_lexer->type, NON_PIPE))
            return(true);
    }
    return(false);
}

static bool iscmd(t_lx *lexer, t_lx *prev_lexer)
{
    if (lexer->type = WORD)
    {
        if (!prev_lexer || prev_lexer->type == WORD || prev_lexer->type == PIPE)
            return (true);
    }
    return (false);
}

static int addcmd(t_cmd *cmd_node, char *cmd, int *i)
{
    cmd_node->cmd[*i] = cmd;
    (*i)--;
}

void    load_cmd_list(t_all *core)
{
    t_lx *lexer;
    t_cmd *cmd;
    int     words_count;

    cmd = galloc(sizeof(t_cmd));
    lexer = getlastnode(getcore()->lexer, "t_lx");
    while (lexer)
    {
        while (lexer->prev)
        {
            if (iscmd(lexer, lexer->prev))
                addcmd(cmd, lexer->content, &words_count);
            else if (isifof(lexer, lexer->prev))
                addifof(cmd, lexer, lexer->prev->type);
        }
        lexer = lexer->prev;
    }
}
