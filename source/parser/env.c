#include "minishell.h"

// static char	*ft_custumjoin(char const *s1, char const *s2)
// {
// 	size_t	s1_len;
// 	size_t	s2_len;
// 	char	*new;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	new = ft_calloc(s1_len + s2_len + 1, sizeof(char));
// 	if (!new)
// 		return (NULL);
// 	ft_memcpy(new, s1, s1_len);
// 	ft_strlcpy(&new[s1_len], s2, s2_len + 1);
// 	return (new);
// }

// static char **setup_path(char **path)
// {
//     int i;
//     char **newpath;

//     i = 0;
//     while (path[i])
//         i++;
//     newpath = ft_calloc(i + 1, sizeof(char *));
//     newpath[i] = NULL;
//     i = -1;
//     while (path[++i])
//         newpath[i] = ft_custumjoin(path[i], "/");
//     return (newpath);
// }

size_t ft_arraylen(char **array)
{
    size_t i;

    if (!array)
        return (0);
    i = 0;
    while (array[i])
        i++;
    return (i);
}

void    fill_path(void)
{
    size_t i;
    size_t len;
    t_env *env;

    //to do:add load PATH variable to core->path
    env = getcore()->env_list; 
    while (env && env->key)
    {
        if (ft_strncmp("PATH", env->key, -1) == 0)
            break;
        env = env->next;
    }
    if (!env || !env->key || ft_strncmp("PATH", env->key, -1))
        return (getcore()->path = NULL, (void)0);
    char **paths = ft_split(env->value, ':');
  if (!paths)
        return (getcore()->path = NULL, (void)0); 
    len = ft_arraylen(paths);
    i = -1;
    getcore()->path = (char **)ft_calloc(len + 1, sizeof(char **));
    while (++i < len)
        getcore()->path[i] = ft_strdup(paths[i]);
    getcore()->path[i] = 0;
}

void   fill_env_list(char *env[])
{
    t_env *env_node;
    int i;

    i = -1;
    getcore()->env = env;
    while (env[++i])
    {
        env_node = ft_calloc(1, sizeof(t_env));
        env_node->key = strchrdup(env[i], ft_strchr(env[i], '='), CALLOC);
        env_node->value = strchrdup(ft_strchr(env[i], '=') + 1, NULL, CALLOC);
        addtolist(env_node, "t_env", NULL);
    }
}
