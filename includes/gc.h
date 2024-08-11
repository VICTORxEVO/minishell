/**
 * @details this header about garbage collector, using linked list to store reference to all allocated memory
 */
#ifndef GC_H
# define GC_H


# include "ext_libs.h"
# include "macros.h"
# include "minishell.h"



typedef struct s_gc
{
    char    *type;
    void    *data;
    t_gc    *next;
}       t_gc;


/**
 * @param list refrance to t_gc
 * @param flag data type need to freed:
 * F_TMP for freeying up all tmp allocation (used after executing commands),
 * F_ALL for freeying up all tmp and perm data (used after exiting the whole program) 
 */
void        clear(char flag);

//clear,print message and exit with exit_code
void        pexit(char *msg, int exit_code);

// set bytes to 0
inline void ft_bzero(void *s, size_t n)
{
	while (n--)
	{
		*(unsigned char *)s = 0;
		s++;
	}
}

inline void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	ptr = malloc(n * size);
	if (!ptr)
		return (NULL);
    ft_bzero(ptr, n * size);
	return (ptr);
}
inline t_gc	*gc_new(void *data)
{
	t_gc	*new;

	new = ft_calloc(1, sizeof(t_gc));
	if (!new)
		pexit(MEM_ERR, 1);
    new->data = data;
}
inline void gc_add_node(void *data)
{
    t_gc *gc_list;

    gc_list = get_core()->gc;
    while (gc_list->next)
    {
            if (!gc_list->data)
            {
                gc_list->data = data;
                return ;
            }
    }
    gc_list->next = gc_new(data);
}

/**
 * @brief garbage collector function
 * 
 * @param size memory size needed just as malloc
 * @return a pointer to memory allocated or exit on failer
 */
inline void *galloc(size_t size)
{
    void *data;

    data = ft_calloc(1, size);
    if (!data)
        (pexit(MEM_ERR, 1));
    gc_add_node(data);
    return (data);
}














#endif