#include "minishell.h"

bool           ft_istoken(int c)
{
    return (c == '>' || c == '<' || c == '|');
}

static bool    ft_isspace2(char *str)
{
    int i;

    while (str[i])
    {
        if (ft_isspace(str[i], NULL))
            return (true);
    }
    return (false);
}
bool	ft_isspace(int c, char *str)
{
    if (str)
        return (ft_isspace2(str));
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

bool ft_isword(int c)
{
    return (ft_isalpha(c) || ft_isalnum || c == '$');
}

t_all   *get_core(void)
{
    static t_all core;

    return (&core);
}
