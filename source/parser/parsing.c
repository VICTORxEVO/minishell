#include "minishell.h"

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

void    reader_loop(void)
{
    char  *line;
    char  *previous_line;

    while (true)
    {
        line = readline(BOLD_MAGENTA"Eureka> "END);
        if (line == NULL || line[0] == 0 || ft_isspace(0, line))
            continue;
            
        getcore()->in_line = line;
        gc_add_node(line);
        previous_line = getcore()->previous_line;
        if (!(previous_line && !ft_strncmp(line, previous_line, -1)))
            add_history(line);
        break;
    }
    if (!ft_strncmp(line, "exit", ft_strlen("exit")))
        pexit(": done!", 1); //tmp function just for debugging and see leaks 
}

static t_env   *fill_env_list(char *env[])
{
    t_env *env_list;
    t_env *head;
    char **key_val;
    t_ndx index;

    ft_bzero(&index, sizeof(t_ndx));
    while (env[index.i])
    {
        if (index.i == 0)
        {
            env_list = ft_calloc(1, sizeof(t_env));
            head = env_list;
        }
        else
        {
            while (env_list->next)
                env_list = env_list->next;
            env_list->next = ft_calloc(1, sizeof(t_env));
            env_list = env_list->next;
        }
        key_val = ft_split(env[index.i++], '=');
        env_list->key =  key_val[0];
        env_list->value = key_val[1];
    }
    return (head);
}
void    parsing(char *env[])
{
    t_all *core;

    core = getcore();
    core->env_list = fill_env_list(env);
    core->inline_len = ft_strlen(core->in_line);
    check_quotes(core->in_line);
    printf("line before->%s\n", core->in_line);
    lexing(core->in_line);
    t_lx *lexer = getcore()->lexer;
	while(lexer)
	{
		printf("lx type -> %d, lx content ->\t%s\\0\n", lexer->type, lexer->content);
		lexer = lexer->next;
	}
    printf("---------------------------\n");
    if (could_expand(core->in_line))
    {
        core->in_line = expand_dollar(core->in_line);
        lexing(core->in_line);
        printf("line after->%s\n", core->in_line);
        lexer = getcore()->lexer;
	    while(lexer)
	    {
		    printf("lx type -> %d, lx content ->\t%s\\0\n", lexer->type, lexer->content);
		    lexer = lexer->next;
	    }
    }
    // check_syntax(core->lexer);
    // final_touch(core->lexer); // remove all kind of quotes in begging or in middle 
    // load_cmd_list(core);
}