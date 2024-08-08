#ifndef GC_H
# define GC_H

# include "ext_libs.h"
# include "macros.h"







typedef struct s_gc
{
    void    *data;
    t_gc    *next;
}       t_gc;


t_gc        *ft_lstnew(void *contant);
int			ft_lstsize(t_gc *lst);
void		ft_lstadd_back(t_gc **lst, t_gc *node);
void		ft_lstclear(t_gc **lst);
void		ft_lstdelone(t_gc *lst);
t_gc		*ft_lstlast(t_gc *lst);
inline void     *malloc_v2(size_t size, t_gc *gc)
{
    void *data;

    data = malloc(size);
    if (!data)
        (pexit(, ))
}














#endif