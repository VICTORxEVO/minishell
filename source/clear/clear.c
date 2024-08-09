#include "gc.h"

static void safe_free(void *data)
{
    if (data)
    {
        free(data);
        data= NULL;
    }
}
void	gc_lstclear(t_gc **lst)
{
	t_gc	*tm;

	if (!lst)
		return ;
	while ((*lst) != NULL)
	{
		tm = (*lst)->next;
		safe_free((*lst)->d_tmp);
		safe_free((*lst)->d_perm);
        safe_free(*lst);
		*lst = tm;
	}
	*lst = NULL;
}

void clear(t_gc **list, char flag)
{
    t_gc *node;

    if (flag == F_TMP)
    {
        node = *list;
        while (node->next)
        {
            if (node->d_tmp)
                safe_free(node->d_tmp);
            node = node->next;
        }
        return ;
    }
    gc_lstclear(list);
}