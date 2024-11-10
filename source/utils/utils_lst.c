#include "minishell.h"

static void     addcmd(t_cmd *node)
{
    t_cmd *cmd;

    cmd = getcore()->cmd;
    if (!cmd)
        getcore()->cmd = (t_cmd *)node;
    else
    {
        while (cmd->next)
            cmd = cmd->next;
        cmd->next = (t_cmd *)node;
    }
}

static void     addenv(t_env *node)
{
    t_env *env_list;

    env_list = getcore()->env_list;
    if (!env_list)
        getcore()->env_list = (t_env *)node;
    else
    {
        while (env_list->next)
            env_list = env_list->next;
        env_list->next = (t_env *)node;
    } 
}

static void    addlexer(t_lx *node)
{
    t_lx *lexer;

    lexer = getcore()->lexer;
    if (!lexer)
    {
        node->prev = NULL;
        getcore()->lexer = (t_lx *)node;
    }
    else
    {
        while (lexer->next)
            lexer = lexer->next;
        node->prev = lexer;
        lexer->next = (t_lx *)node;
    }
}

void    addtolist(void *node, char *list_type)
{
    if (!ft_strncmp(list_type, "t_lx", -1))
        addlexer((t_lx *)node);
    else if (!ft_strncmp(list_type, "t_env", -1))
        addenv((t_env *)node);
    else if (!ft_strncmp(list_type, "t_cmd", -1))
        addcmd((t_cmd *)node);
}

void    *getlastnode(void *list, char *list_type)
{
    if (list && !ft_strncmp(list_type, "t_lx", -1))
    {
        while (((t_lx *)list)->next)
            list = ((t_lx *)list)->next;
    }
     return (list);
}