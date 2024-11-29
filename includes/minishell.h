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
    char            **cmd;
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
    char            **env;
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



/*          >Parsing Functions<           */
/**
 * @brief Main parsing function that handles the command line input
 * @details Processes user input through lexical analysis, expansion and command loading
 */
void        parsing(void);

/**
 * @brief Validates quote pairs in the input string
 * @details Checks for matching single and double quotes, exits with error if unmatched
 * @param line Input string to check
 */
void        check_quotes(char *line);
int         skipquotes(char *str);
bool        wordstart(char a, char b, int i, int maxlen);

/**
 * @brief Expands environment variables in a string
 * @details Replaces $VAR with its value from environment
 * @param line String containing variables to expand
 * @return New string with expanded variables
 */
char        *expand_dollar(char *line);

/**
 * @brief Handles special variable expansion for $$ and $?
 * @details Expands $$ to PID and $? to last exit code
 * @param index Current position in string
 * @param type Type of special variable ('$' or '?')
 * @return Length of expanded value
 */
int         get_var_special(int *index, char type);

/**
 * @brief Performs lexical analysis on input string
 * @details Splits input into tokens (words, operators, etc)
 * @param line Input string to tokenize
 */
void        lexing(char *line);

/**
 * @brief Expands variables in lexer tokens
 * @details Processes variable expansion for each word token
 * @param lexer Linked list of lexer tokens
 */
void        expanding(t_lx *lexer);

/**
 * @brief Creates command structures from lexer tokens
 * @details Groups tokens into command structures with I/O redirections
 * @param core Main shell structure containing lexer tokens
 */
void        load_cmd_list(t_all *core);
/*          >Execution Functions<           */
/**
 */
int     is_builtin(char *cmd);
int     exec_builtin(t_cmd * cmd);
int     ifd(char *filename);
int     ofd(char *filename, char mode);
void    hd_fork(char *tmpfile, char *delimit);
int     hd(char *delimit);


/*          >bultin functions<           */

int     ft_cd(t_cmd *cmd);
int     ft_echo(t_cmd *cmd);
int     ft_pwd();
int     ft_env();
int     ft_export(t_cmd *cmd);
int     ft_unset(t_cmd *cmd);

/*          builtin utils               */
int     ft_setenv(char *name, char *val, int overwrite);
char    *ft_getenv(char *cmd);


/*          builtin export utils        */
t_env   *ft_copy_node(t_env *node);
t_env   *ft_copy_env();
t_env   *ft_sort_export(t_env *export);
void    ft_swap_nodes(t_env *outer,  t_env *inner);
void    free_env(t_env *env);


/*          builtin export utils 2     */
int         ft_print_export();


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
void        addtolist(void *node, char *list_type, void *head);
char        *strchrdup(char *str, char *delimit, bool type);
void        *getlastnode(void *list, char *list_type);
t_lx        *splitcontent(char *str);
void        fill_path(void);


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
void    print_cmd(void);


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
