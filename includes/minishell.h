/**
 * @details minishell main header still under devlopment 
 */
#ifndef MINISHELL_H
# define MINISHELL_H



# include "gc.h"


typedef struct s_lx
{
    unsigned char type;
    char *content;
    struct s_lx *next;
}   t_lx;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}       t_env;

typedef struct s_cmd
{
    char type;
    char *delimiter;
    char **cmd;
    char *infile;
    char *outfile;

}       t_cmd;

typedef struct s_all
{
    t_env *env_list;
    char **env;
    unsigned int    cmd_count;
    unsigned int    pipe_count;
    char *in_line;
    size_t inline_len;
    t_cmd  **cmd_scope;
    t_gc    *gc;
    t_lx *lexer;
    unsigned char exit_code;
}       t_all;



void    check_quotes(char *line);
void    load_elements(char *line);
void    parsing(char *env[]);
long long lexer_add_token(char type);
long long lexer_add_word(char type, char *line);








/*          >Utils functions<           */
/**
 * @brief this function called whatever you need to use the main struct, its like a global varibale
 * @return refrence the t_core struct
 */
t_all   *get_core(void);
bool     ft_isword(int c);
bool     ft_isspace(int c, char *str);
bool     ft_istoken(int c);
char    *strtkr_gen(char type);
void    reader_loop(void);
























#endif
