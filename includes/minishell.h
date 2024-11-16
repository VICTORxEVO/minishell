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
    struct s_lx     *prev;
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
    t_lx            *scope;
    int             ifd;
    int             ofd;
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
    char            **path;
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
char        *expand_dollar(char *line);
int         get_var_special(int *index, char type);
void        lexing(char *line);
void        expanding(t_lx *lexer);



/*          >Utils functions<           */
/**
 * @brief this function called whatever you need to use the main struct, its like a global varibale
 * @return refrence the t_core struct
 */
t_all       *getcore(void);
bool        ft_isword(int c);
bool        ft_isspace(int c, char *str);
bool        istoken(int c, bool type);
char        *strtkr_gen(char type);
void        reader_loop(void);
bool        needexpand(char *str);
int         get_dollar(char *str, bool *flag);
t_var       *handle_list(void);
char        *get_end_addr(char *str);
bool        possible_expand(char c);
void        strocpy(char *dest, const char * src, int len);
bool        is_str_havespace(char *string);
void        addtolist(void *node, char *list_type);
char        *strchrdup(char *str, char *delimit, bool type);
void        *getlastnode(void *list, char *list_type);
t_lx        *splitcontent(char *str);


/*          >Utils of parsing functions<           */
/**
 * 
 */
void        addoldhistory(void);
char        *create_prompt(void);
bool        needspliting(t_lx *lexer, t_lx *prev_lexer);
bool        checkspace_str(char *str);
void        final_touch(t_lx *lexer);



/**          >Printing/Debuging funtions<          */
/**
 * 
 */
void    print_lx(void);
void    print_env(void);


/**
 * @brief Fills the environment list with environment variables
 * @param env Array of environment variable strings
 */
void fill_env_list(char *env[]);

/**
 * @brief Adds a new lexer list segment between existing nodes
 * @param new_list New lexer list to insert
 * @param lexer Current lexer node 
 * @param prev_lx Previous lexer node
 * @param next_lx Next lexer node
 * @return Pointer to the inserted list
 */
t_lx *addnewlist(t_lx *new_list, t_lx *lexer, t_lx *prev_lx, t_lx *next_lx);


#endif
