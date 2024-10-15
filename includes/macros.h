/**
 * @details this header contain all macros nedded in the program 
 */
#ifndef MACROS_H
# define MACROS_H


// macros for perror message
# define PRGM_NAME "minishell"
# define MEM_ERR ": malloc"
# define DQ_ERR ": syntax error: unclosed token `\"'"
# define SQ_ERR ": syntax error: unclosed token `''"
# define PIPE_ERR ": syntax error: unclosed token `|'"


/**
 * @brief macros for "clear" function
 * 
 * @see galloc()
 */
# define F_ALL 10
# define F_TMP 11

/**
 * @brief macros for tokens and syntax
 */

// macro for empty variable
# define EMPTY_VAR 0

// double quotes ascii
# define D_QUOTES 34

// single quotes ascii
# define S_QUOTES 39

// heredoc
# define HERE_DOC 1

// infile redirection in overwrite mode
# define IN_RDRT 2

// outfile redirection in overwrite mode
# define OUT_RDRT_OW 3

// outfile redirection in appende mode
# define OUT_RDRT_APP 4

// word type token 
# define WORD 10

//word in double quotes
# define WORD_D_QUOTES 11

//word in single quotes
#define WORD_S_QUOTES 12

// pipe type token
# define PIPE 20

// any token type
# define TOKEN 21



















#endif