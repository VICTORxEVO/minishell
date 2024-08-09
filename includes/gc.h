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


void		gc_lstclear(t_gc **lst);
void        clear(t_gc **list, char flag);
void        pexit(t_gc **gc, char *msg, int exit_code);
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