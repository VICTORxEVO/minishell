#include "minishell.h"

bool    is_str_havespace(char *string)
{
    int i;

    i = 0;
    while (string[i])
    {
        if (ft_isspace(string[i], NULL))
            return (true);
    }
    return (false);
}



void    strocpy(char *dest, const char *src, int len)
{
	int	x;

	x = -1;
    if (!src)
        return;
    if (len < 0)
    {
        while (src[++x])
		    dest[x] = src[x];
        return ;
    }
	while (++x < len)
		dest[x] = src[x];
}

bool    possible_expand(char c)
{
    return (c == '$' || c == '?' || ft_isspace(c, NULL));
}

char    *get_end_addr(char *str)
{
    while (*str)
        str++;
    return (str);
}

t_var *handle_list(void)
{
    t_var *list;

    list = getcore()->var_list;
    if (!list)
    {
        list = galloc(sizeof(t_var));
        getcore()->var_list = list;
    }
    else
    {
        while(list->next)
            list = list->next;
        list->next = galloc(sizeof(t_var));
        list = list->next;
    }
    return (list);
}
