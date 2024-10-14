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

// double quotes ascii
# define D_QUOTES 34

// single quotes ascii
# define S_QUOTES 39 // single quotes ascii

// heredoc
# define HERE_DOC 0

// infile redirection in overwrite mode
# define IN_RDRT 1

// outfile redirection in overwrite mode
# define OUT_RDRT_OW 2

// outfile redirection in appende mode
# define OUT_RDRT_APP 3

// word type token 
# define WORD 4

//word in double quotes
# define WORD_D_QUOTES 5

//word in single quotes
#define WORD_S_QUOTES 6


// pipe type token
# define PIPE 7

// any token type
# define TOKEN 8



















#endif