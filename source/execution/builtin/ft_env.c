

#include "minishell.h"


char    *ft_getenv(char *cmd)
{
    t_env * env;

    env = getcore()->env_list; 
    while (env)
    {
        if (ft_strcmp(env->key, cmd) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}


int    ft_env()
{
    t_env * env;

    env = getcore()->env_list;
    if (env == NULL)
        return (1);
    while (env)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
    return (0);
}
