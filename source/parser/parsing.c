#include "minishell.h"

void    reader_loop(void)
{
    char  *line;

    while (true)
    {
        line = readline("Eurika ✨➜ ");
        if (getcore()->sig_init || getcore()->sig_init)
            continue;
        if (!line)
            (clear(FREE_ALL), exit(getcore()->exit_code));
        if (line[0] == 0 || ft_isspace(0, line))
        {
            if (line)
                free(line);
            continue;
        }
        getcore()->in_line = line;
        (gc_add_node(line), add_history(line));
        break ;
    }
}

bool    parsing(void)
{
    t_all *core;

    core = getcore();
    core->inline_len = ft_strlen(core->in_line);
    if (!check_quotes(core->in_line) || !lexing(core->in_line))
        return (false);
    if (needexpand(core->in_line, NULL))
        expanding(core->lexer);
    final_touch(core->lexer); // remove all kind of quotes in begging or in middle 
    load_cmd_list(core);
    if (!prepare_heredoc(core->cmd))
        return (false);
    return (true);
}
