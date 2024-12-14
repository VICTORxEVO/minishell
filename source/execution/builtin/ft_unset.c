#include "minishell.h"

int     ft_add_node(t_env *last_node, char *new_key, char *new_val)
{
    t_env *env;

    if (!last_node)
        return (0);
    env = ft_calloc(1, sizeof(t_env));
    if (!env)
        return (0);
    env->key = new_key;
    env->value = new_val;
    addtolist(env, "t_env", NULL);
    return (1);
}

void    ft_remove_node(char *node)
{
    t_env *env;
    t_env *prev;

    env = getcore()->env_list;
    prev = NULL;
    while (env)
    {
        if (ft_strcmp(env->key, node) == 0)
        {
            if (prev == NULL)
                getcore()->env_list = env->next;
            else
                prev->next = env->next;
            (free(env->key), free(env->value));
            free(env);
            break;
        }
        prev = env;
        env = env->next;
    }
}

static void update_env_value(t_env *env, char *val, int overwrite)
{
    char *tmp;

    if ((overwrite == 2) && val)
    {
        tmp = env->value;
        env->value = ft_strjoin_m(env->value, val);
        free(tmp);
        free(val);
    }
    else if (overwrite == 1 && val)
    {
        free(env->value);
        env->value = val;
    }
}

/**  @brief same as the orignal setenv(3), 
*    except tar9i3a of overwrite == 2 
*    for appending env variable with += 
*      
*   @param overwrite Determines the behavior when the variable already exists:
*                  - 0: Do not overwrite the existing value.
*                  - 1: Overwrite the existing value with the new value.
*                  - 2: Append the new value to the existing value using `+=`. 
*   @return 1 on success, 0 on failure.
*/
int     ft_setenv(char *key, char *val, int overwrite)
{
    t_env *env;
    bool found;

    env = getcore()->env_list;
    found = false;
    while (env)
    {
        if (ft_strcmp(key, env->key) == 0)
        {
            update_env_value(env, val, overwrite);
            found = true;
            break;
        }
        env = env->next;
    }
    if (!found)
    {
        if (ft_add_node(getlastnode(getcore()->env_list, "t_env"), key, val) == 0)
            return (1);
    }
    return (0);
}


int     ft_unset(t_cmd *cmd)
{
    t_env *env;

    env = getcore()->env_list;
    while (env && cmd->cmd[1])
    {
        if (ft_strcmp(env->key, cmd->cmd[1]) == 0)
            return (ft_remove_node(cmd->cmd[1]), 0);
        env = env->next;
    }
    return (0);
}
