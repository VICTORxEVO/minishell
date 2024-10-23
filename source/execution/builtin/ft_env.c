





#include "minishell.h"


char    *ft_getenv(t_cmd *cmd)
{
    t_env * env;

    env = get_core()->env_list;
    if (!env)
    {
        // to check in case of no env exist.
        printf("NO environment found\n");
        return (NULL);
    }
    while (env)
    {
        if (ft_strcmp(env->key, cmd->cmd[1]))
            return (env->value);
        env = env->next;
    }
    return (NULL);
}


int    ft_env(t_cmd *cmd)
{
    t_env * env;

    env = get_core()->env_list;
    if (env == NULL);
    {
        //print error here
        //assign default environemt or print that the minishell mightn't function properly 
        //same as bash
        printf("\n");
        return (0);
    }
    while (env)
    {
        printf("%s=%s", env->key, env->value);
        env = env->next;
    }
    printf("\n");
    return (1);
}
