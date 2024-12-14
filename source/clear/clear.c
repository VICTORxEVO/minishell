#include "minishell.h"

static void re_zero(void)
{
    t_all *core;
    void *data;
    void **data1;
    void **data2;
    unsigned char value;

    core = getcore();
    //keep env_list and exit code because its needed while program run time
    value = core->exit_code;
    data = (void *)core->env_list;
    data1 = (void **)core->path;
    data2 = (void **)core->env;
    ft_bzero(getcore(), sizeof(t_all)); // init all struct with 0;
    core->exit_code = value;
    core->env_list = (t_env *)data;
    core->path = (char **)data1;
    core->env = (char **)data2;
}

void safe_free(void **data)
{
    if (*data)
    {
        free(*data);
        *data = NULL;
    }
}

static void env_lstclear(void)
{
    t_env *env_list;
    t_env *tmp;

    env_list = getcore()->env_list;
    while (env_list)
    {
        tmp = env_list->next;
        safe_free((void **)&env_list->key);
        safe_free((void **)&env_list->value);
        safe_free((void **)&env_list);
        env_list = tmp;
    }
}
static void gc_lstclear(void)
{
	t_all	*core;
    t_gc    *tmp;

    core = getcore();
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
    if (flag == FREE_ALL)
    {
        env_lstclear();
        safe_free((void **)&getcore()->previous_line);
        free2d((void **)getcore()->path);
        free2d((void **)getcore()->env);
    }
}
