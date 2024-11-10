#include "minishell.h"

void    reader_loop(void)
{
    char  *line;
    char  *previous_line;
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
        previous_line = getcore()->previous_line;
        add_history(line);
        break ;
    }
    if (!ft_strncmp(line, "exit", ft_strlen("exit")))
        pexit(": done!", 1); //tmp function just for debugging and see leaks 
}

void    parsing(char *env[])
{
    t_all *core;

    core = getcore();
    fill_env_list(env);
    core->inline_len = ft_strlen(core->in_line);
    check_quotes(core->in_line);
    lexing(core->in_line);
    // print_env();
    print_lx();
    // core->in_line = heredoc_case(getcore()->lexer);
    if (could_expand(core->in_line))
    {
        pexit(": feature not availble yet, please try another thing!", 1);
        core->in_line = expand_dollar(core->in_line);
        lexing(core->in_line);
        printf("line after->%s\n", core->in_line);
        print_lx();
    }
    // final_touch(core->lexer); // remove all kind of quotes in begging or in middle 
    // load_cmd_list(core);
}
