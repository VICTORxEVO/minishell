#include "minishell.h"

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
		return (pexit("malloc", MALLOC_CODE, EXIT), NULL);
    new->data = data;
	return (new);
}

inline void gc_add_node(void *data)
{
    t_gc *gc_list;

    gc_list = getcore()->gc;
    if (!gc_list)
        getcore()->gc = gc_new(data);
    else
    {
        while (gc_list->next)
        {
            if (!gc_list->data)
            {
                gc_list->data = data;
                return ;
            }
            gc_list = gc_list->next;
        }
        gc_list->next = gc_new(data);
    }
}

inline void *galloc(size_t size)
{
    void *data;

    data = ft_calloc(1, size);
    if (!data)
        return (pexit("malloc", MALLOC_CODE, EXIT), NULL);
    gc_add_node(data);
    return (data);
}