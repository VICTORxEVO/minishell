#include "minishell.h"

void    addoldhistory(void)
{
    char *home;
    

    home = getenv("HOME");
    if (!home)
        exit (200);
}

static char	*ft_csubstr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_l;

	if (!s)
		return (NULL);
	s_l = ft_strlen(s);
	if (start >= s_l)
		return (ft_calloc(1, sizeof(char)));
	if (start + len >= s_l)
	{
		sub = malloc(sizeof(char) * (s_l - start + 1));
		if (!sub)
			return (NULL);
		ft_strlcpy(sub, &s[start], (s_l - start + 1));
	}
	else
	{
		sub = malloc(sizeof(char) * (len + 1));
		if (!sub)
			return (NULL);
		ft_strlcpy(sub, &s[start], (len + 1));
	}
	return (sub);
}

char    *strchrdup(char *str, char *delimit, bool type)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (&str[i] == delimit && type == CALLOC)
            return (ft_csubstr(str, 0, i));
        else if (&str[i] == delimit && type == GALLOC)
            return (ft_substr(str, 0, i));
    }
    if (type == CALLOC)
        return(ft_csubstr(str, 0, i));
    return (ft_substr(str, 0, i));
}
