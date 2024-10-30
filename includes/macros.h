/**
 * @details this header contain all macros nedded in the program 
 */
#ifndef MACROS_H
# define MACROS_H


// macros for perror message
# define PRGM_NAME "Eureka"
# define MEM_ERR ": malloc"
# define DQ_ERR ": syntax error: unclosed token `\"'"
# define SQ_ERR ": syntax error: unclosed token `''"
# define PIPE_ERR ": syntax error: empty pipe `|'"
# define TOKEN_ERR ": sytax_error: unexpected token after `"
# define PTR_ERR ": clear_1data(): data pointer not found !"
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
# define PIPE -1

// any token type
# define TOKEN -2

//for all whitespace charachters
# define IS_SPACE " \t\v\n\r\f"










#ifndef COLORS_H
# define COLORS_H

// Regular text colors
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"

// Bold text colors
#define BOLD_BLACK "\033[1;30m"
#define BOLD_RED "\033[1;31m"
#define BOLD_GREEN "\033[1;32m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_BLUE "\033[1;34m"
#define BOLD_MAGENTA "\033[1;35m"
#define BOLD_CYAN "\033[1;36m"
#define BOLD_WHITE "\033[1;37m"

// Underlined text colors
#define UNDERLINE_BLACK "\033[4;30m"
#define UNDERLINE_RED "\033[4;31m"
#define UNDERLINE_GREEN "\033[4;32m"
#define UNDERLINE_YELLOW "\033[4;33m"
#define UNDERLINE_BLUE "\033[4;34m"
#define UNDERLINE_MAGENTA "\033[4;35m"
#define UNDERLINE_CYAN "\033[4;36m"
#define UNDERLINE_WHITE "\033[4;37m"

// Background colors
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

// Reset color
#define END "\033[0m"

#endif // COLORS_H






#endif