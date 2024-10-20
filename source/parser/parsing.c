#include "minishell.h"

static void    load_elements(char *line)
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
        else if (line[i] == D_QUOTES)
            i += lexer_add_word(WORD_D_QUOTES, line + i) + 2;
        else if (line[i] == S_QUOTES)
            i += lexer_add_word(WORD_S_QUOTES, line + i) + 2;
        else if (line[i] != 0)
            i += lexer_add_word(WORD, line + i);
    }
}

void    reader_loop(void)
{
    char  *line;

    while (true)
    {
        line = readline(BOLD_MAGENTA"Eureka> "END);
        if (line == NULL || line[0] == 0 || ft_isspace(0, line))
            continue;
            
        get_core()->in_line = line;
        gc_add_node(line);
        break;
    }
    if (!ft_strncmp(line, "exit", ft_strlen("exit")))
        pexit(": done!", 1); //tmp function just for debugging and see leaks 
}


t_env   *fill_env_list(char *env[])
{
    t_env *env_list;

    size_t i = 0;
    size_t j = 0;
    char **key_val;

    while (env[i])
        i++;
    env_list = (t_env *) ft_calloc(i,  sizeof(t_env));
    //error
    if (!env_list)
        return (NULL);
    while (j < i)
    {
        key_val = ft_split(env[j++], '=');
        printf("key_val => [%s , %s]\n", key_val[0], key_val[1]); 
        env_list->key =  key_val[0];
        env_list->value = key_val[1]; 
        env_list = env_list->next;
    }
    env_list->next = NULL;
    return (env_list);
}
void    parsing(char *env[])
{
    t_all *core;

    core = get_core();
    core->env = env;
    core->env_list = fill_env_list(env);

    // while (core->env_list->next)
    // {
    //     printf("key = %s, val = %s\n", core->env_list->key, core->env_list->value);
    //     core->env_list = core->env_list->next;
    // }

    core->inline_len = ft_strlen(core->in_line);
    check_quotes(core->in_line);
    load_elements(core->in_line);
    expand_dollar(core->lexer);
    check_syntax(core->lexer);
    // load_cmd_list(core);
}