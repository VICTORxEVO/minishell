/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:40:27 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 13:40:28 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/**
 * Error Message Macros
 * These macros define standard error messages used throughout the shell program
 */

/** Program name displayed in error messages */
# define PRGM_NAME "Eureka"

/** Double quote syntax error message for unclosed quotes */
# define DQ_ERR ": syntax error: unclosed token `\"'"

/** Single quote syntax error message for unclosed quotes */
# define SQ_ERR ": syntax error: unclosed token `''"

/** Generic token syntax error message */
# define TOKEN_ERR ": syntax error near token `"

/** Invalid pointer error message for data cleanup */
# define PTR_ERR ": clear_1data(): data pointer not found !"

/** Critical error messages that will cause shell exit */
# define FATAL_ERR "\033[1;31mFATAL:\033[0m "

/**
 * @brief Clear operation modes

	* @details Specifies which memory blocks should be cleared during
    cleanup operations
 *
 * @note Used by clear() function to determine cleanup scope
 * @see galloc() Function responsible for memory allocation
 * @see clear() Function that performs the cleanup
 */
typedef enum e_clear_mode
{
	FREE_ALL = 10, /**< Free all allocated memory blocks in the program */
	FREE_TEMP = 11 /**< Free only temporary memory blocks */
}	t_clear_mode;

/**
 * @brief ASCII quote character values
 * @details Contains ASCII values for quote characters used in parsing
 */
typedef enum e_quote_type
{
	D_QUOTES = 34,
	S_QUOTES = 39
}	t_quote_type;

/*
 * Token Types Overview:
 * This section defines the different types of tokens used by the shell parser:
 * - Command operators (pipe)
 * - Redirections (heredoc, input, output)
 * - Words (commands and arguments)
 * The token type determines how each part of the command line gets processed.
 */

typedef enum e_token_type
{
	TOKEN = -2,
	PIPE = -1,
	HERE_DOC = 1,
	IN_RDRT,
	OUT_RDRT_OW,
	AMBIG_RDRT,
	HERE_DOC_FD,
	OUT_RDRT_APP,
	WORD = 10,
}	t_token_type;

/*
 * Error Codes:
 * Standard error codes used throughout the shell for:
 * - System call failures (fork, pipe, open, etc)
 * - Command execution errors
 * - Permission issues
 * - Signal handling
 * These help identify where and why an operation failed.
 */

typedef enum e_error_code
{
	DUP2_CODE = 2,
	CLOSE_CODE,
	PIPE_CODE,
	READ_CODE,
	OPEN_CODE,
	WRITE_CODE,
	FORK_CODE,
	MALLOC_CODE,
	READLINE_CODE,
	AMBIG_CODE = 20,
	PERM_DENIED_CODE = 126,
	CMD_NOTFOUND_CODE = 127,
	SIG_BASE_CODE = 128,
	GNRL_CODE = 1
}	t_error_code;

/**
 * @brief Enum representing pipe ends in a Unix pipe
 *
 * In Unix/Linux systems, pipes have two ends:
 * - READ_END (0): The reading end of the pipe where data is received
 * - WRITE_END (1): The writing end of the pipe where data is sent
 */
typedef enum e_pipe_end
{
	READ_END = 0,
	WRITE_END = 1
}	t_pipe_end;

/**
 * @brief Memory allocation type flags
 * @details Specifies which allocation function to use in strchrdup
 */
typedef enum e_allocation_type
{
	GALLOC = 0,
	CALLOC = 1
}	t_allocation_type;

/**
 * @brief Token checking mode flags
 * @details Specifies which tokens to check in istoken function
 */
typedef enum e_token_check_mode
{
	NON_PIPE = 0,
	ALL_TKN = 1
}	t_token_check_mode;

typedef enum e_overwrite_mode
{
	NO_OVERWRITE = 0,
	OVERWRITE = 1,
	APPEND = 2
}	t_overwrite_mode;

// for all whitespace charachters
# define IS_SPACE " \t\v\n\r\f"

// bash special charachters
# define SP_CHARACTERS "?*&|;"

// child process macro
# define CHILD 0

// heredoc tmp file name
# define HERE_DOC_FILE "/tmp/tmp.hzxcd512ek"

// macro for empty variable
# define EMPTY_VAR 0

// mods for load_cmd
# define COUNT 0
# define LOAD 1

// macro for backup to restore fd
# define RESTORE -1

// macro for command not found
# define CMD_NOTFOUND ": command not found !"

// macro for cmd permition denied
# define PERM_DENIED ": permission denied !"

// macro for cmd if is a dirrectory
# define CMD_DIR ": Is a directory !"

// macro pexit func to exit ot not
# define EXIT 1

// macro for ambigous redirection
# define AMBIG_ERR ": ambiguous redirect !"

// exit built in right usage
# define EXIT_USAGE ": exit: usage: exit [N]\nN must be >= 0 and <= 255"

// macros for signal handler
# define SG_HD_MODE 1

# define HD_WARNING ": warning: here-document delimited \
 by end-of-file (wanted `%s')\n"

# define HD_TMP_FAIL ": heredoc: Warning: Failed to remove temporary file"

// Regular text colors
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

// Bold text colors
# define BOLD_BLACK "\033[1;30m"
# define BOLD_RED "\033[1;31m"
# define BOLD_GREEN "\033[1;32m"
# define BOLD_YELLOW "\033[1;33m"
# define BOLD_BLUE "\033[1;34m"
# define BOLD_MAGENTA "\033[1;35m"
# define BOLD_CYAN "\033[1;36m"
# define BOLD_WHITE "\033[1;37m"

// Underlined text colors
# define UNDERLINE_BLACK "\033[4;30m"
# define UNDERLINE_RED "\033[4;31m"
# define UNDERLINE_GREEN "\033[4;32m"
# define UNDERLINE_YELLOW "\033[4;33m"
# define UNDERLINE_BLUE "\033[4;34m"
# define UNDERLINE_MAGENTA "\033[4;35m"
# define UNDERLINE_CYAN "\033[4;36m"
# define UNDERLINE_WHITE "\033[4;37m"

// Background colors
# define BG_BLACK "\033[40m"
# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN "\033[46m"
# define BG_WHITE "\033[47m"

// Reset color
# define END "\033[0m"

#endif