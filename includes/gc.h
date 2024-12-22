/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:10:32 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 16:10:33 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @details this header about garbage collector, using linked list to store
 * reference to all allocated memory
 */
#ifndef GC_H
# define GC_H

# include "ext_libs.h"
# include "macros.h"

typedef struct s_all	t_all;

typedef struct s_gc
{
	void				*data;
	struct s_gc			*next;
}						t_gc;

/**
 * Cleans up allocated memory based on flag type
 * @param flag Cleanup mode:
 *        FREE_TEMP: Free temporary allocations used during command execution
 *        FREE_ALL: Free all allocations before program exit
 */
void					clear(char flag);

/**
 * Gets reference to global shell state
 * @return Pointer to main shell state structure
 */
extern t_all			*getcore(void);

/**
 * Prints error message and exits program
 * @param msg Error message to display
 * @param exit_code Exit status code to use
 * @param exit Whether to exit program after message
 */
void					pexit(char *msg, short int exit_code, bool exit);

/**
 * Creates new garbage collector node
 * @param data Pointer to allocated memory to track
 * @return New GC node or NULL on failure
 */
t_gc					*gc_new(void *data);

/**
 * Adds allocated memory to garbage collector list
 * @param data Pointer to memory to track
 */
void					gc_add_node(void *data);

/**
 * Allocates memory and adds to garbage collector
 * @param size Number of bytes to allocate
 * @return Pointer to allocated memory or exits on failure
 */
void					*galloc(size_t size);

/**
 * Safely frees memory and nulls pointer
 * @param data Pointer to pointer to free
 */
void					safe_free(void **data);

/**
 * Removes single item from garbage collector
 * @param data Pointer to memory to remove
 */
void					clear_1data(void *data);

/**
 * Clears entire linked list of specified type
 * @param list Pointer to list head
 * @param list_type String identifying list type
 */
void					clear_1list(void *list, char *list_type);

/**
 * Frees array of pointers and the array itself
 * @param array Array of pointers to free
 */
void					free2d(void **array);

#endif