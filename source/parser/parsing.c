#include "minishell.h"

static char *reader_loop(void)
{
    char *line;

    while (true)
    {
        line = readline("minishell> ");
        if (line == NULL || line[0] == 0 || ft_isspace(0, line))
            continue;
        return (line);
    }
    return (NULL);
}

static void preprocess(char *line)
{
    check_quotes(line);
    check_pipe(line);
    check_tokens(line);
}

void    parsing(char *env[])
{
    t_all *core

    core = get_core();
    core->env = env;
    core->in_line = reader_loop();
    core->inline_len = ft_strlen(core->in_line);
    preprocess(line);
    load_elements(line);
}