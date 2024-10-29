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

typedef struct s_file
{
    char mode;
    char *content;
    struct s_file *next;
}       t_file;


typedef struct s_cmd
{
    char            type;
    char            *delimiter;
    char            **cmd;
    t_file          *infile;
    t_file          *outfile;
    struct s_cmd    *next;
}       t_cmd;

typedef struct s_var
{
    char        *content;
    int         start_ndx;
    int         end_ndx;
    struct s_var *next;
}       t_var;

typedef struct s_all
{
    t_cmd           *cmd;
    t_env           *env_list;
    t_lx            *lexer;
    t_gc            *gc;
    unsigned int    cmd_count;
    unsigned int    pipe_count;
    unsigned char   exit_code;
    char            *in_line;
    size_t          inline_len;
    t_var           *var_list;
    char            *previous_line;
}       t_all;

typedef struct s_ndx
{
    int i;
    int j;
    int k;
    int l;
    int m;
    int n;
    int d;
    int t;
}       t_ndx;



/*          >Parsing Funtions<           */
/**
 */
void        parsing(char *env[]);
void        check_quotes(char *line);
void        check_syntax(t_lx *lexer);
long long   lexer_add_token(char type);
long long   lexer_add_word(char type, char *line);
void        expand_dollar(t_lx *lexer);
int         get_var_special(int *index, char type);




/*          >Utils functions<           */
/**
 * @brief this function called whatever you need to use the main struct, its like a global varibale
 * @return refrence the t_core struct
 */
t_all       *getcore(void);
bool        ft_isword(int c);
bool        ft_isspace(int c, char *str);
bool        is_token(int c);
char        *strtkr_gen(char type);
void        reader_loop(void);
bool        could_expand(char *str);
bool        is_token_err(t_lx *lx, t_lx *next_lx);
bool        is_pipe_err(t_lx *lx, t_lx *next_lx);
int         get_dollar(char *str, bool *flag);
t_var       *handle_list(void);
char        *get_end_addr(char *str);
bool        possible_expand(char c);
void        strocpy(char *dest, const char * src, int len);
bool        is_str_havespace(char *string);



void        safe_free(void **data);













#endif
