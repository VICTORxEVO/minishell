#include "minishell.h"

void    update_env(t_env *env_list)
{
    t_ndx i;
    t_env *tmp;

    ft_bzero(&i, sizeof(t_ndx));
    tmp = env_list;
    while(tmp)
    {
        i.l++;
        tmp = tmp->next;
    }
    free2d((void **)getcore()->env);
    getcore()->env = ft_calloc(i.l + 1, sizeof(char *));
    while (env_list)
    {
        getcore()->env[i.i++] = ft_strjoin_m(ft_strjoin_m(env_list->key, "="), env_list->value);
    }
}


void    ft_update_path(void)
{
    t_env *env;

    env = getcore()->env_list;
    free2d((void **)getcore()->path);
    while (env && env->key)
    {
        if (ft_strncmp("PATH", env->key, -1) == 0)
        {
            getcore()->path = ft_split_path(env->value, ':');
            break;
        }
        env = env->next;
    }
}

void   fill_env_list(char *env[])
{
    t_env *env_node;
    int i;

    i = -1;
    while (env[++i])
    {
        env_node = ft_calloc(1, sizeof(t_env));
        env_node->key = strchrdup(env[i], ft_strchr(env[i], '='), CALLOC);
        env_node->value = strchrdup(ft_strchr(env[i], '=') + 1, NULL, CALLOC);
        addtolist(env_node, "t_env", NULL);
    }
    ft_update_path();
}
