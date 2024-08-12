/**
 * @details minishell main header still under devlopment 
 */
#ifndef MINISHELL_H
# define MINISHELL_H



# include "libft.h"
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
    char *full_cmd;
    char *cmd;
    char *infile;
    char *outfile;

}       t_cmd;


typedef struct s_all
{
    t_env *env;
    unsigned int    cmd_count;
    t_lx    *lexer;
    t_cmd  **scopes;
    t_gc    *gc;
    char exit_code;
}   t_all;

t_all *core;





/*          >Utils functions<           */
/**
 * @brief this function called whatever you need to use the main struct, its like a global varibale
 * @return refrence the t_core struct
 */
t_all   *get_core(void)




























#endif
