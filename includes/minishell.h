/**
 * @details minishell main header still under devlopment 
 */
#ifndef MINISHELL_H
# define MINISHELL_H



# include "ext_libs.h"
# include "gc.h"



typedef struct s_lx
{
    unsigned char type;
    char *contant;
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
    t_env *env;
    unsigned int    cmd_count;
    unsigned int    pipe_count;
    char *in_line;
    size_t inline_len;
    t_cmd  **cmd_scope;
    t_gc    *gc;
    t_lx *lexer;
    char exit_code;
}   t_all;
t_all *core;









/*          >Utils functions<           */
/**
 * @brief this function called whatever you need to use the main struct, its like a global varibale
 * @return refrence the t_core struct
 */
t_all   *get_core(void);
bool     ft_isword(int c);
bool     ft_isspace(int c, char *str);
bool     ft_istoken(int c);



























#endif
