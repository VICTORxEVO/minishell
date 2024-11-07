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
static void    lexing(char *line)
{
    long long i;

    i = 0;
    while (line[i])
    {
        while (line[i] && ft_isspace(line[i], NULL))
            i++;
        if (line[i + 1] && line[i] == '<' && line[i + 1] == '<')
            i += lexer_add_token(HERE_DOC);
        else if (line[i + 1] && line[i] == '>' && line[i + 1] == '>')
            i += lexer_add_token(OUT_RDRT_APP);
        else if (line[i] == '<')
            i += lexer_add_token(IN_RDRT);
        else if (line[i] == '>')
            i += lexer_add_token(OUT_RDRT_OW);
        else if (line[i] == '|')
            i += lexer_add_token(PIPE);
        else if (line[i])
            i += lexer_add_word(WORD, line + i);
    }
}


static void   fill_env_list(char *env[])
{
    t_env *env_node;
    int i;

    i = -1;
    while (env[++i])
    {
        env_node = ft_calloc(1, sizeof(t_env));
        env_node->key = strchrdup(env[i], ft_strchr(env[i], '='), CALLOC);
        env_node->value = strchrdup(ft_strchr(env[i], '=') + 1, NULL, CALLOC);
        addtolist(env_node, "t_env");
    }
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
    if (could_expand(core->in_line))
    {
        pexit(": feature not availble yet, please try another thing!", 1);
        core->in_line = expand_dollar(core->in_line);
        lexing(core->in_line);
        printf("line after->%s\n", core->in_line);
        print_lx();
    }
    check_syntax(core->lexer);
    // final_touch(core->lexer); // remove all kind of quotes in begging or in middle 
    load_cmd_list(core);
}