/**
 * @details this header about garbage collector, using linked list to store reference to all allocated memory
 */
#ifndef GC_H
# define GC_H


# include "ext_libs.h"
# include "macros.h"


typedef struct s_all t_all;

typedef struct s_gc
{
    void    *data;
    struct s_gc *next;
}       t_gc;

/**
 * @param list refrance to t_gc
 * @param flag data type need to freed:
 * FREE_TEMP for freeying up all tmp allocation (used after executing commands),
 * FREE_ALL for freeying up all tmp and perm data (used after exiting the whole program) 
 */
void        clear(char flag);

extern t_all   *getcore(void);

//clear,print message and exit with exit_code
void        pexit(char *msg, int exit_code);

// set bytes to 0

t_gc	*gc_new(void *data);

void gc_add_node(void *data);

/**
 * @brief garbage collector function
 * 
 * @param size memory size needed just as malloc
 * @return a pointer to memory allocated or exit on failer
 */
void *galloc(size_t size);




void        safe_free(void **data);
void        clear_1data(void *data);







#endif