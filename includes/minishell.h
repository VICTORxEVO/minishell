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
    char            *original_content;
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
    int             unsed_fd;
    struct s_cmd    *next;
}       t_cmd;

typedef struct s_var
{
    char        *content;
    int         start_ndx;
    int         end_ndx;
    struct s_var *next;
}       t_var;


/**
 * @struct s_builtin
 * @brief Structure representing a built-in command.
 *
 * This structure holds the name of the built-in command and a function pointer
 * to the function that implements the command.
 *
 * @var s_builtin::name
 * The name of the built-in command.
 *
 * @var s_builtin::func
 * Function pointer to the function that implements the built-in command.
 * The function takes a pointer to a t_cmd structure as an argument and returns an integer.
 */
typedef struct s_builtin {
    char *name;
    int (*func)(t_cmd *);
} t_builtin;

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
    t_var           *var_list;
    pid_t           *pids;
    bool            error_flag;
    int             gnl_fd;
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
bool        parsing(void);

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
 * @return Length of expanded value
 */
int         get_var_special(int *index);

/**
 * @brief Performs lexical analysis on input string
 * @details Splits input into tokens (words, operators, etc)
 * @param line Input string to tokenize
 */
bool        lexing(char *line);

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

void        load_cmd(t_cmd *cmd_list);
/*          >Execution Functions<           */
/**
 */
int     is_builtin(char *cmd);
int     exec_builtin(t_cmd * cmd);
void    execution(void);
char    *getcmdpath(char *cmd);
void    close_allhd(t_lx *lexer);
bool    emptyword(t_lx *lexer);
bool    gen_newpip(int *pip, t_cmd *cmd);


/**
 * @brief Fork helper that executes different functions in parent and child
 * @param child_fn Function pointer for child process
 * @param child_arg Argument for child function 
 * @param parent_fn Function pointer for parent process
 * @param parent_arg Argument for parent function
 * @return Process ID in parent, -1 on error, child never returns
 */
pid_t   forker(void (*child_fn)(void *), void *child_arg, 
                    void (*parent_fn)(void *, pid_t), void *parent_arg);


/*          >Redirection Functions<           */
/**
 * @brief Opens a file for input redirection
 * @details Opens the specified file in read-only mode
 * @param filename Name of the file to open
 * @return File descriptor of the opened file, or -1 on error
 */
int     ifd(char *filename);

/**
 * @brief Opens a file for output redirection
 * @details Opens the specified file in write or append mode based on the mode parameter
 * @param filename Name of the file to open
 * @param mode Mode to open the file in (overwrite or append)
 * @return File descriptor of the opened file, or -1 on error
 */
int     ofd(char *filename, char mode);

/**
 * @brief Handles here-document input
 * @details Reads input from the user until the delimiter is encountered and stores it in a temporary file
 * @param delimit Delimiter string to end the here-document input
 * @return File descriptor of the temporary file containing the here-document input
 */
int     hd(char *delimit);

/**
 * @brief Duplicates file descriptors for input and output redirection
 * @details Uses dup2 to duplicate the file descriptors for standard input and output
 * @param ifd Input file descriptor to duplicate
 * @param ofd Output file descriptor to duplicate
 * @return true on success, false on error
 */
bool    duping(int ifd, int ofd);

bool    prepare_ifof(t_cmd *cmd_list);
bool    backup_fd(int *fd);
bool    open_allhd(t_lx *lexer);
void    exec_cmdchild(void *data);
void    exec_cmdparent(void *data, pid_t pid);

/*          >bultin functions<           */

int     ft_cd(t_cmd *cmd);
int     ft_echo(t_cmd *cmd);
int     ft_pwd();
int     ft_env();
int     ft_export(t_cmd *cmd);
int     ft_unset(t_cmd *cmd);
int     ft_exit();

/*          builtin utils               */
void     ft_setenv(char *name, char *val, int overwrite);
char    *ft_getenv(char *var);


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
bool        needexpand(char *str, t_lx *lexer);
int         get_dollar(char *str, bool *flag);
t_var       *handle_list(void);
char        *get_end_addr(char *str);
bool        possible_expand(char c);
void        strocpy(char *dest, const char * src, int len);
bool        is_str_havespace(char *string);
void        addtolist(void *node, char *list_type, void *head);
char        *strchrdup(const char *str, char *delimit, bool type);
void        *getlastnode(void *list, char *list_type);
t_lx        *splitcontent(char *str);
void        sighandler(bool mode);
void        updatePath(void);



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