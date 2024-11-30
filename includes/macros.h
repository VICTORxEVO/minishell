/**
 * @details this header contain all macros nedded in the program 
 */
#ifndef MACROS_H
# define MACROS_H


/**
 * Error Message Macros
 * These macros define standard error messages used throughout the shell program
 */

/** Program name displayed in error messages */
#define PRGM_NAME "Eureka"

/** Double quote syntax error message for unclosed quotes */
#define DQ_ERR ": syntax error: unclosed token `\"'"

/** Single quote syntax error message for unclosed quotes */  
#define SQ_ERR ": syntax error: unclosed token `''"

/** Generic token syntax error message */
#define TOKEN_ERR ": syntax error near token `"

/** Invalid pointer error message for data cleanup */
#define PTR_ERR ": clear_1data(): data pointer not found !"


/**
 * @brief Clear operation modes
 * @details Specifies which memory blocks should be cleared during cleanup operations
 * 
 * @note Used by clear() function to determine cleanup scope
 * @see galloc() Function responsible for memory allocation
 * @see clear() Function that performs the cleanup
 */
typedef enum e_clear_mode {
    FREE_ALL = 10,  /**< Free all allocated memory blocks in the program */
    FREE_TEMP = 11  /**< Free only temporary memory blocks */
} t_clear_mode;

/**
 * @brief ASCII quote character values
 * @details Contains ASCII values for quote characters used in parsing
 */
typedef enum e_quote_type {
    D_QUOTES = 34,  /**< ASCII value for double quote (") character */
    S_QUOTES = 39   /**< ASCII value for single quote (') character */
} t_quote_type;


/**
 * @brief Enum representing all token types in the shell
 *
 * This enumeration defines constants for:
 * @param PIPE (-1): Pipe operator token to connect commands
 * @param TOKEN (-2): Generic token identifier
 * @param HERE_DOC (1): Read input from a here document (<<)
 * @param IN_RDRT (2): Input file redirection (<)
 * @param OUT_RDRT_OW (3): Output file redirection, overwrite mode (>)
 * @param OUT_RDRT_APP (4): Output file redirection, append mode (>>)
 * @param WORD (10): Regular command or argument token
 *
 * Usage examples:
 * - PIPE: cmd1 | cmd2
 * - HERE_DOC: cmd << EOF
 * - IN_RDRT: cmd < input.txt
 * - OUT_RDRT_OW: cmd > output.txt
 * - OUT_RDRT_APP: cmd >> output.txt
 * - WORD: Regular command names and arguments
 */
typedef enum e_token_type
{
    PIPE = -1,           /* Pipe operator token */
    TOKEN = -2,          /* Generic token identifier */
    HERE_DOC = 1,        /* Here document redirection */
    IN_RDRT = 2,         /* Input file redirection */
    OUT_RDRT_OW = 3,     /* Output file redirection (overwrite mode) */
    OUT_RDRT_APP = 4,    /* Output file redirection (append mode) */
    WORD = 10            /* Regular word token */
} t_token_type;


/**
 * @brief System call error codes
 * @details Enumeration of error codes used to identify which system call failed
 *          during process execution and error handling
 */
typedef enum e_error_code
{
    DUP2_CODE = 2,   /**< Error code for dup2() system call failure */
    CLOSE_CODE,      /**< Error code for close() system call failure */
    PIPE_CODE,       /**< Error code for pipe() system call failure */
    READ_CODE,       /**< Error code for read() system call failure */
    OPEN_CODE,       /**< Error code for open() system call failure */
    WRITE_CODE,      /**< Error code for write() system call failure */
    FORK_CODE,       /**< Error code for fork() system call failure */
    MALLOC_CODE,     /**< Error code for malloc() function failure */
    READLINE_CODE    /**< Error code for readline() function failure */
} t_error_code;


/**
 * @brief Enum representing pipe ends in a Unix pipe
 * 
 * In Unix/Linux systems, pipes have two ends:
 * - READ_END (0): The reading end of the pipe where data is received
 * - WRITE_END (1): The writing end of the pipe where data is sent
 */
typedef enum e_pipe_end
{
    READ_END = 0,    /* File descriptor for reading from pipe */
    WRITE_END = 1    /* File descriptor for writing to pipe */
} t_pipe_end;


/**
 * @brief Memory allocation type flags
 * @details Specifies which allocation function to use in strchrdup
 */
typedef enum e_allocation_type {
    GALLOC = 0,    /**< Use galloc allocation function */
    CALLOC = 1     /**< Use calloc allocation function */
} t_allocation_type;


/**
 * @brief Token checking mode flags
 * @details Specifies which tokens to check in istoken function
 */
typedef enum e_token_check_mode {
    NON_PIPE = 0,  /**< Check all tokens except pipe token */
    ALL_TKN = 1    /**< Check all tokens including pipe token */
} t_token_check_mode;


//for all whitespace charachters
# define IS_SPACE " \t\v\n\r\f"

//bash special charachters
# define SP_CHARACTERS "?*&|;"

//child process macro
# define CHILD 0

//heredoc tmp file name 
# define HERE_DOC_FILE "/tmp/tmp.hzxcd512ek"

// macro for empty variable
# define EMPTY_VAR 0

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


#endif