/**
 * @details this header about garbage collector, using linked list to store reference to all allocated memory
 */
#ifndef GC_H
# define GC_H


# include "ext_libs.h"
# include "macros.h"




typedef struct s_gc
{
    char    *type;
    void    *d_tmp;
    void    *d_perm;
    t_gc    *next;
}       t_gc;


/**
 * @param list refrance to t_gc
 * @param flag data type need to freed:
 * F_TMP for freeying up all tmp allocation (used after executing commands),
 * F_ALL for freeying up all tmp and perm data (used after exiting the whole program) 
 */
void        clear(t_gc **list, char flag);

// clear whole list
void		gc_lstclear(t_gc **lst);

//clear,print message and exit with exit_code
void        pexit(t_gc **gc, char *msg, int exit_code);

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
inline t_gc	*gc_new(void *content, char flag, t_gc *gc)
{
	t_gc	*new;

	new = ft_calloc(1, sizeof(t_gc));
	if (!new)
		pexit(&gc, MEM_ERR, 1);
    if (flag = D_TMP)
        new->d_tmp = content;
    else
        new->d_perm = content;
}
inline void gc_add_node(t_gc *gc_list, void *data, char type)
{
    while (gc_list->next)
    {
        if (type == D_TMP)
        {
            if (!gc_list->d_tmp)
            {
                gc_list->d_tmp = data;
                return ;
            }
        }
        else
        {
            if (!gc_list->d_perm)
            {
                gc_list->d_perm = data;
                return ;
            }
        }
    }
    gc_list->next = gc_new(data, type, gc_list);
}

/**
 * @brief garbage collector function
 * 
 * @param size memory size needed just as malloc
 * @param type type of data returned:
 * D_TMP for temporary data that nedded for one commande cycle and freed at end of executing the commands,
 * D_PERM for permanent data that nedded for the whole program.
 * @param gc a double pointer refrence to the t_gc
 * @return a pointer to memory allocated or exit on failer
 */
inline void *malloc_v2(size_t size, char type, t_gc **gc)
{
    void *data;

    data = ft_calloc(1, size);
    if (!data)
        (pexit(gc, MEM_ERR, 1));
    gc_add_node(*gc, data, type);
    return (data);
}














#endif