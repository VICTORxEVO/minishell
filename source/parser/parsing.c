#include "minishell.h"

void    reader_loop(void)
{
    char  *line;

    while (true)
    {
        line = readline("Eurika ✨➜ ");
        if (!line)
            (clear(FREE_ALL), exit(getcore()->exit_code));
        if (line[0] == 0 || ft_isspace(0, line))
        {
            if (line)
                free(line);
            continue;
        }
        getcore()->in_line = line;
        gc_add_node(line);
        add_history(line);
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
    if (needexpand(core->in_line))
        expanding(core->lexer);
    final_touch(core->lexer); // remove all kind of quotes in begging or in middle 
    
    // printf(BOLD_MAGENTA "╔══════════════════════════════════════════════════════╗\n");
    // printf("║              PARSER: AFTER FINAL TOUCH               ║\n");
    // printf("╚══════════════════════════════════════════════════════╝\n" END);
    // print_lx();
    
    load_cmd_list(core);

    // printf(BOLD_CYAN "\n╔═══════════════════ COMMAND LIST ═══════════════════╗\n");
    // printf("║         Displaying parsed command structure         ║\n");
    // printf("╚════════════════════════════════════════════════════╝\n" END);
    return (true);
}
