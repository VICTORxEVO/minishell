#include "minishell.h"

void    reader_loop(void)
{
    char  *line;
    // char  *previous_line;
    char *prompt;

    while (true)
    {
        prompt = create_prompt();
        line = readline(prompt);
        if (line == NULL || line[0] == 0 || ft_isspace(0, line))
        {
            if (line)
                free(line);
            continue;
        }
        getcore()->in_line = line;
        gc_add_node(line);
        // previous_line = getcore()->previous_line;
        add_history(line);
        break ;
    }
    if (!ft_strncmp(line, "exit", ft_strlen("exit")))
        pexit(": done!", FREE_ALL); //tmp function just for debugging and see leaks 
}

void    parsing(void)
{
    t_all *core;

    core = getcore();
    core->inline_len = ft_strlen(core->in_line);
    check_quotes(core->in_line);
    lexing(core->in_line);
    print_lx();
    if (needexpand(core->in_line))
    {
        printf(BOLD_RED "Feature not available: This functionality is still under development. Please try again later.\n" END);
        return ;
        expanding(core->lexer);
    }
    final_touch(core->lexer); // remove all kind of quotes in begging or in middle 
    
    printf(BOLD_MAGENTA "╔══════════════════════════════════════════════════════╗\n");
    printf("║              PARSER: AFTER FINAL TOUCH               ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n" END);
    print_lx();
    
    load_cmd_list(core);

    printf(BOLD_CYAN "\n╔═══════════════════ COMMAND LIST ═══════════════════╗\n");
    printf("║         Displaying parsed command structure         ║\n");
    printf("╚════════════════════════════════════════════════════╝\n" END);
    
    print_cmd();
}
