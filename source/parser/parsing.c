#include "minishell.h"

void    reader_loop(void)
{
    char  *line;

    while (true)
    {
        line = readline("minishell> ");
        if (line == NULL || line[0] == 0 || ft_isspace(0, line))
            continue;
            
        get_core()->in_line = line;
        gc_add_node(line);
        break;
    }
    if (!ft_strncmp(line, "exit", ft_strlen("exit")))
        pexit(" :done!", 1); //tmp function just for debugging and see leaks 
}

void    parsing(char *env[])
{
    t_all *core;

    core = get_core();
    core->env = env;
    core->inline_len = ft_strlen(core->in_line);
    check_quotes(core->in_line);
    load_elements(core->in_line);
}