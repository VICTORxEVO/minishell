

#include "minishell.h"


char    *ft_getenv(char *var)
{
    t_env * env;

    env = getcore()->env_list; 
    while (env)
    {
        if (ft_strcmp(env->key, var) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}


int    ft_env(t_cmd *cmd)
{
    t_env * env;

    (void*)cmd;
    env = getcore()->env_list;
    if (env == NULL)
        return (1);
    while (env)
    {
        if (env->value)
            printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
    return (0);
}
