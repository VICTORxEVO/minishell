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

    if ((overwrite == APPEND) && val)
    {
        tmp = env->value;
        env->value = ft_strjoin_m(env->value, val);
        free(tmp);
        free(val);
    }
    else if (overwrite == OVERWRITE && val)
    {
        free(env->value);
        env->value = val;
    }
}

/**
 * @brief Sets or updates an environment variable
 * @details Same as the original setenv(3), except for overwrite == APPEND for appending env variable with `+=`
 * @param key Name of the environment variable
 * @param val Value of the environment variable
 * @param overwrite Determines the behavior when the variable already exists:
 *                  - NO_OVERWRITE: Do not overwrite the existing value.
 *                  - OVERWRITE: Overwrite the existing value with the new value.
 *                  - APPEND: Append the new value to the existing value using `+=`.
 */
void     ft_setenv(char *key, char *val, int overwrite)
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
            return ;
        }
        env = env->next;
    }
    if (!found)
    {
        if (ft_add_node(getlastnode(getcore()->env_list, "t_env"), key, val) == 0)
            return ;
    }
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
