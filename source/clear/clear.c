#include "minishell.h"

static void safe_free(void *data)
{
    if (data)
    {
        free(data);
        data = NULL;
    }
}

static void env_lstclear(void)
{
    t_all *core;
    t_env *tmp;

    core = get_core();
    while (core->env)
    {
        tmp = core->env_list->next;
        safe_free(core->env_list->key);
        safe_free(core->env_list->value);
        core->env_list = tmp;
    }
}
static void gc_lstclear(void)
{
	t_all	*core;
    t_gc    *tmp;

    core = get_core();
	if (!core->gc)
		return ;
	while (core->gc)
	{
		tmp = core->gc->next;
		safe_free(core->gc->data);
        safe_free(core->gc);
		core->gc = tmp;
	}
	core->gc = NULL;
}

void clear(char flag)
{
    t_gc *gc;

    if (flag == F_TMP)
    {
        gc = get_core()->gc;
        while (gc->next)
        {
            if (gc->data)
                safe_free(gc->data);
            gc = gc->next;
        }
    }
    else
    {
        gc_lstclear();
        env_lstclear();
    }
}
