#include "minishell.h"

static void re_zero(void)
{
    t_all *core;
    void *data;
    unsigned char value;

    core = get_core();
    //keep env_list and exit code because its needed while program run time
    data = (void *)core->env_list;
    value = core->exit_code;
    ft_bzero(get_core(), sizeof(t_all)); // init all struct with 0;
    core->env_list = (t_env *)data;
    core->exit_code = value;
}

static void safe_free(void **data)
{
    if (*data)
    {
        free(*data);
        *data = NULL;
    }
}

static void env_lstclear(void)
{
    t_all *core;
    t_env *tmp;

    core = get_core();
    while (core->env_list)
    {
        tmp = core->env_list->next;
        safe_free((void **)&core->env_list->key);
        safe_free((void **)&core->env_list->value);
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
		safe_free((void **)&core->gc->data);
        safe_free((void **)&core->gc);
		core->gc = tmp;
	}
	core->gc = NULL;
}

void clear(char flag)
{
    gc_lstclear();
    re_zero();
    if (flag == F_ALL)
        env_lstclear();
}
