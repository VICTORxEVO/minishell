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

void    fill_path(void)
{
    //to do:add load PATH variable to core->path
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
        addtolist(env_node, "t_env");
    }
}
