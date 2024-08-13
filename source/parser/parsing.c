#include "minishell.h"

static char *reader_loop(void)
{
    char *line;

    while (true)
    {
        line = readline("minishell> ");
        if (line == NULL || line[0] == 0)
            continue;
        return (line);
    }
    return (NULL);
}

static void preprocess(char *line)
{
    t_lx    lexer;

    check_pre_syntax(line);
}

void    parsing(char *env[])
{
    t_all *core;
    char *line;

    core = get_core();
    core->env = env;
    core->input_line = reader_loop();
    preprocess(line);
}