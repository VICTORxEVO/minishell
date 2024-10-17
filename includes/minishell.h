/**
 * @details minishell main header still under devlopment 
 */
#ifndef MINISHELL_H
# define MINISHELL_H



# include "gc.h"


typedef struct s_lx
{
    char   type;
    char            *content;
    struct s_lx     *next;
}   t_lx;

typedef struct s_env
{
    char            *key;
    char            *value;
    struct s_env    *next;
}       t_env;

typedef struct s_cmd
{
    char            type;
    char            *delimiter;
    char            **cmd;
    char            *infile;
    char            *outfile;

}       t_cmd;

typedef struct s_all
{
    t_cmd           **cmd_scope;
    t_env           *env_list;
    t_lx            *lexer;
    t_gc            *gc;
    unsigned int    cmd_count;
    unsigned int    pipe_count;
    unsigned char   exit_code;
    char            **env;
    char            *in_line;
    size_t          inline_len;
}       t_all;



/*          >Parsing Funtions<           */
/**
 */
void        parsing(char *env[]);
void        check_quotes(char *line);
void        check_syntax(t_lx *lexer);
long long   lexer_add_token(char type);
long long   lexer_add_word(char type, char *line);

/*          >Execution Functions<           */
/**
 */
int     is_builtin(char *cmd);


/*          >Utils functions<           */
/**
 * @brief this function called whatever you need to use the main struct, its like a global varibale
 * @return refrence the t_core struct
 */
t_all       *get_core(void);
bool        ft_isword(int c);
bool        ft_isspace(int c, char *str);
bool        is_token(int c);
char        *strtkr_gen(char type);
void        reader_loop(void);
bool        could_expand(char *str);
bool        is_token_err(t_lx *lx, t_lx *next_lx);
bool        is_pipe_err(t_lx *lx, t_lx *next_lx);












#endif
