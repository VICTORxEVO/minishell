/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:32:29 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 19:45:51 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "gc.h"

typedef struct s_lx
{
	char			type;
	char			*content;
	char			*original_content;
	struct s_lx		*next;
	struct s_lx		*prev;
}					t_lx;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	t_lx			*scope;
	char			**cmd;
	int				ifd;
	int				ofd;
	int				unsed_fd;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_var
{
	char			*content;
	int				start_ndx;
	int				end_ndx;
	struct s_var	*next;
}					t_var;

typedef struct s_all
{
	t_cmd			*cmd;
	t_env			*env_list;
	t_lx			*lexer;
	char			**env;
	t_gc			*gc;
	char			**path;
	unsigned int	cmd_count;
	unsigned int	pipe_count;
	unsigned char	exit_code;
	char			*in_line;
	t_var			*var_list;
	pid_t			*pids;
	bool			error_flag;
	int				gnl_fd;
	bool			hd_mode;
	bool			subshell;
}					t_all;

typedef struct s_ndx
{
	int				i;
	int				j;
	int				k;
	int				l;
	int				m;
	int				n;
	int				d;
	int				t;
}					t_ndx;

/*          >Parsing Functions<           */
/*
 * >Parsing Functions<

	* This section contains the core parsing functionality
     for the shell interpreter.
 * These functions handle lexical analysis, command parsing, token processing,
 * and preparation of commands for execution.
 */

/**
 * Performs the complete parsing process for a command line input.
 * Coordinates lexing, expansion and command loading.
 * @return true if parsing succeeded, false if errors occurred
 */
bool				parsing(void);

/**
 * Moves past quoted sections in a string.
 * @param str The string to process
 * @return Number of characters skipped
 */
int					skipquotes(char *str);

/**
 * Determines if a position marks the start of a new word.
 * @param a Current character
 * @param b Next character
 * @param i Current position
 * @param maxlen Maximum length to check
 * @return true if position starts a new word
 */
bool				wordstart(char a, char b, int i, int maxlen);

/**
 * Expands environment variables in a line prefixed with $.
 * @param line Input string to expand
 * @return New string with expanded variables
 */
char				*expand_dollar(char *line);

/**
 * Handles special variable expansion like $?.
 * @param index Current position in string
 * @return Length of expanded content
 */
int					get_var_special(int *index);

/**
 * Performs lexical analysis to break input into tokens.
 * @param line Input command line
 * @return true if lexing succeeded, false if errors
 */
bool				lexing(char *line);

/**
 * Expands variables in lexer tokens.
 * @param lexer Linked list of tokens
 */
void				expanding(t_lx *lexer);

/**
 * Creates command structures from lexer tokens.
 * @param core Main shell state structure
 */
void				load_cmd_list(t_all *core);

/**
 * Loads command arguments into command structure.
 * @param cmd_list Command to load arguments into
 */
void				load_cmd(t_cmd *cmd_list);

/**
 * Main input reading loop for the shell.
 * Handles line reading and history.
 */
void				reader_loop(void);

/**
 * Checks if a string needs variable expansion.
 * @param str String to check
 * @param lexer Current lexer token
 * @return true if expansion needed
 */
bool				needexpand(char *str, t_lx *lexer);

/**
 * Locates next $ character for expansion.
 * @param str String to search
 * @param flag Status flag
 * @return Position of next $
 */
int					get_dollar(char *str, bool *flag);

/**
 * Splits content into multiple lexer tokens.
 * @param str Content to split
 * @return New linked list of tokens
 */
t_lx				*splitcontent(char *str);

/**
 * Performs final processing on lexer tokens.
 * Handles quote removal and empty tokens.
 * @param lexer Token list to process
 */
void				final_touch(t_lx *lexer);

/**
 * Adds new token list into existing lexer chain.
 * @param new_list List to add
 * @param lexer Current token
 * @param prev_lx Previous token
 * @param next_lx Next token
 * @return Updated token list
 */
t_lx				*addnewlist(t_lx *new_list, t_lx *lexer, t_lx *prev_lx,
						t_lx *next_lx);

/*          >Execution Functions<           */
/*
 * >Execution Functions<
 * This section contains the core command execution functionality of the shell.
 * These functions handle running commands, managing processes,
	setting up pipes,
 * and coordinating parent/child process execution flow.
 */

/**
 * Checks if a command name matches a builtin command.
 * @param cmd Command name to check
 * @return 1 if command is builtin, 0 otherwise
 */
int					is_builtin(char *cmd);

/**
 * Executes a builtin command.
 * @param cmd Command structure containing arguments
 * @return Exit status of the builtin command
 */
int					exec_builtin(t_cmd *cmd);

/**
 * Main command execution coordinator.
 * Handles execution of both single commands and command pipelines.
 */
void				execution(void);

/**
 * Resolves full path for an executable command.
 * Searches PATH environment for command location.
 * @param cmd Command name to resolve
 * @return Full path to executable or NULL if not found
 */
char				*getcmdpath(char *cmd);

/**
 * Creates a new pipe for command pipeline.
 * @param pip Array to store pipe file descriptors
 * @param cmd Command structure to set pipe FDs on
 * @return true on success, false on error
 */
bool				gen_newpip(int *pip, t_cmd *cmd);

/**
 * Manages process forking and parent/child execution.
 * @param child_fn Function to run in child process
 * @param child_arg Argument for child function
 * @param parent_fn Function to run in parent process
 * @param parent_arg Argument for parent function
 * @return Process ID of child or -1 on error
 */
pid_t				forker(void (*child_fn)(void *), void *child_arg,
						void (*parent_fn)(void *, pid_t), void *parent_arg);

/**
 * Child process execution handler.
 * Sets up redirections and executes command.
 * @param data Command structure to execute
 */
void				exec_cmdchild(void *data);

/**
 * Parent process execution handler.
 * Manages child process and handles cleanup.
 * @param data Command structure being executed
 * @param pid Process ID of child
 */
void				exec_cmdparent(void *data, pid_t pid);

/*          >Here Document Functions<           */
/*
 * >Here Document Functions<

	* This section contains functions for handling here documents (heredocs)
    in the shell.

	* Here documents allow reading input until a specified delimiter
    is encountered,
 * similar to << in bash. These functions manage heredoc creation,
	cleanup and setup.
 */

/**
 * Creates a here document and reads input until delimiter is found.
 * @param delimit String that marks the end of heredoc input
 * @return File descriptor for reading the heredoc content, or negative on error
 */
int					hd(char *delimit);

/**
 * Closes all active here document file descriptors.
 * Should be called when heredocs are no longer needed.
 * @param lexer Lexer token list containing heredoc tokens
 */
void				close_allhd(t_lx *lexer);

/**
 * Sets up all here documents needed by the command.
 * Reads input for each heredoc and stores for later use.
 * @param lexer Lexer token list to process
 * @return true if all heredocs were created successfully, false on error
 */
bool				open_allhd(t_lx *lexer);

/*          >Redirection Functions<           */
/*
 * >Redirection Functions<

	* This section contains functions for handling input/output
    redirection in the shell.
 * These functions manage file descriptor operations, file opening/closing,
 * and stream redirection for commands.
 */

/**
 * Duplicates input and output file descriptors.
 * @param ifd Input file descriptor to duplicate
 * @param ofd Output file descriptor to duplicate
 * @return true if duplication succeeded, false on error
 */
bool				duping(int ifd, int ofd);

/**
 * Prepares input/output file descriptors for a command.
 * Handles all redirections specified in the command.
 * @param cmd_list Command structure containing redirection info
 * @return true if setup succeeded, false on error
 */
bool				prepare_ifof(t_cmd *cmd_list);

/**
 * Backs up original file descriptors for later restoration.
 * @param fd Array to store backup file descriptors
 * @return true if backup succeeded, false on error
 */
bool				backup_fd(int *fd);

/**
 * Opens a file for input redirection.
 * @param filename Name of file to open for reading
 * @return File descriptor or negative on error
 */
int					ifd(char *filename);

/**
 * Opens a file for output redirection.
 * @param filename Name of file to open for writing
 * @param mode Redirection mode (truncate/append)
 * @return File descriptor or negative on error
 */
int					ofd(char *filename, char mode);

/*          >Builtin Functions<           */
/*
 * >Builtin Functions<
 * This section contains implementations of shell builtin commands.
 * These are commands that are executed directly by the shell rather than
 * as external programs. They have direct access to the shell's internal state.
 */

/**
 * Changes the current working directory.
 * @param cmd Command structure containing path argument
 * @return Exit status (0 on success, >0 on error)
 */
int					ft_cd(t_cmd *cmd);

/**
 * Displays text to standard output.
 * @param cmd Command structure containing strings to echo
 * @return Exit status (0 on success, >0 on error)
 */
int					ft_echo(t_cmd *cmd);

/**
 * Prints the current working directory.
 * @return Exit status (0 on success, >0 on error)
 */
int					ft_pwd(void);

/**
 * Displays all environment variables.
 * @return Exit status (0 on success, >0 on error)
 */
int					ft_env(void);

/**
 * Sets or modifies environment variables.
 * @param cmd Command structure containing variables to export
 * @return Exit status (0 on success, >0 on error)
 */
int					ft_export(t_cmd *cmd);

/**
 * Removes environment variables.
 * @param cmd Command structure containing variables to unset
 * @return Exit status (0 on success, >0 on error)
 */
int					ft_unset(t_cmd *cmd);

/**
 * Exits the shell with optional status code.
 * @param cmd Array of command arguments where:
 *            cmd[0] is "exit"
 *            cmd[1] (optional) is the numeric exit status
 * @return Exit status code:
 *         - The specified exit code if valid number provided (0-255)
 *         - Previous exit code if no argument given
 *         - 2 if invalid argument provided
 */
int					ft_exit(char **cmd);

/*          Environment Variable Functions          */
/*
 * Core functions for managing environment variables in the shell.
 * Provides ability to get, set and modify environment variables.
 */

/**
 * Sets/updates an environment variable
 * @param name Variable name
 * @param val Variable value
 * @param overwrite How to handle existing variables:
 *                  0: Don't overwrite
 *                  1: Overwrite
 *                  2: Append with +=
 */
void				ft_setenv(char *name, char *val, int overwrite);

/**
 * Gets value of environment variable
 * @param var Variable name to lookup
 * @return Value of variable or NULL if not found
 */
char				*ft_getenv(char *var);

/*          builtin export utils        */
t_env				*ft_copy_node(t_env *node);
t_env				*ft_copy_env(void);
t_env				*ft_sort_export(t_env *export);
void				ft_swap_nodes(t_env *outer, t_env *inner);
void				free_env(t_env *env);
int					ft_print_export(void);

/*          >Export Utility Functions<           */
/**
 * Creates a copy of an environment variable node
 * @param node Node to copy
 * @return New copy of the node
 */
t_env				*ft_copy_node(t_env *node);

/**
 * Creates a copy of entire environment list
 * @return New copy of environment list
 */
t_env				*ft_copy_env(void);

/**
 * Sorts environment variables for export display
 * @param export List to sort
 * @return Sorted list
 */
t_env				*ft_sort_export(t_env *export);

/**
 * Swaps two environment nodes during sorting
 * @param outer First node
 * @param inner Second node
 */
void				ft_swap_nodes(t_env *outer, t_env *inner);

/**
 * Frees environment list and its contents
 * @param env List to free
 */
void				free_env(t_env *env);

/**
 * Prints environment variables in export format
 * @return Exit status
 */
int					ft_print_export(void);

/*          >Utility Functions<           */
/**
 * Gets reference to main shell state structure
 * Acts as pseudo global variable
 * @return Pointer to core structure
 */
t_all				*getcore(void);

/**
 * Checks if character is whitespace in string
 * @param c Character to check
 * @param str String context
 * @return true if whitespace
 */
bool				ft_isspace(int c, char *str);

/**
 * Checks if character is a shell token
 * @param c Character to check
 * @param type Token type to check for
 * @return true if character is token
 */
bool				istoken(int c, bool type);

/**
 * Generates string of tokens by type
 * @param type Token type to generate
 * @return String containing tokens
 */
char				*strtkr_gen(char type);

/**
 * Gets/creates variable handling list
 * @return List for variable handling
 */
t_var				*handle_list(void);

/**
 * Gets pointer to end of string
 * @param str String to process
 * @return Pointer to string end
 */
char				*get_end_addr(char *str);

/**
 * Checks if character can be expanded
 * @param c Character to check
 * @return true if expandable
 */
bool				possible_expand(char c);

/**
 * Custom string copy with length limit
 * @param dest Destination buffer
 * @param src Source string
 * @param len Maximum length to copy
 */
void				strocpy(char *dest, const char *src, int len);

/**
 * Checks if string contains spaces
 * @param string String to check
 * @return true if contains spaces
 */
bool				is_str_havespace(char *string);

/**
 * Adds node to typed list
 * @param node Node to add
 * @param list_type List type identifier
 * @param head List head pointer
 */
void				addtolist(void *node, char *list_type, void *head);

/**
 * Duplicates string up to delimiter
 * @param str Source string
 * @param delimit Delimiter string
 * @param type Delimiter matching type
 * @return New string or NULL
 */
char				*strchrdup(const char *str, char *delimit, bool type);

/**
 * Gets last node in typed list
 * @param list List to traverse
 * @param list_type List type identifier
 * @return Pointer to last node
 */
void				*getlastnode(void *list, char *list_type);

/*             >Signal Functions<                 */
/*
 * Functions for handling signal management in the shell.
 * Handles SIGINT (Ctrl+C),
	SIGQUIT (Ctrl+\) and other signal related functionality.
 */

/**
 * Sets up signal handlers for the shell.
 * @param mode Operation mode:
 *        0: Normal shell mode
 *        1: Here document mode (SG_HD_MODE)
 */
void				sighandler(bool mode);

/*          >Utils of parsing functions<           */
/*
 * Utility functions used during command parsing and processing.
 * These help with token analysis and string manipulation tasks.
 */

/**
 * Checks if a lexer token needs to be split into multiple tokens.
 * @param lexer Current token being checked
 * @param prev_lexer Previous token in chain
 * @return true if token needs splitting, false otherwise
 */
bool				needspliting(t_lx *lexer, t_lx *prev_lexer);

/**
 * Checks if a string contains only whitespace characters.
 * @param str String to check
 * @return true if string is all whitespace, false otherwise
 */
bool				checkspace_str(char *str);

/**
 * Checks if a word token is empty or only contains whitespace.
 * @param lexer Token to check
 * @return true if word is empty, false otherwise
 */
bool				emptyword(t_lx *lexer);

/*           >Environment Functions<                */
/*
 * Functions for managing shell environment variables.
 */

/**
 * Initializes environment variable list from main argv env.
 * @param env Array of environment strings from main
 */
void				fill_env_list(char *env[]);

/**
 * Updates PATH environment variable in internal structures.
 * Called after environment modifications.
 */
void				updatepath(void);

#endif