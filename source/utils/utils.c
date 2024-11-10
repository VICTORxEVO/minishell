#include "minishell.h"

bool	istoken(int c, bool type)
{
	if (type == ALL_TKN)
	return (c == '>' || c == '<' || c == '|' || (c >= HERE_DOC
			&& c <= OUT_RDRT_APP) || c == PIPE);
	else
		return (c == '>' || c == '<' || c == '|' || (c >= HERE_DOC
			&& c <= OUT_RDRT_APP));
}

static bool	ft_isspace2(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isspace(str[i], NULL))
			return (false);
	}
	return (true);
}
bool	ft_isspace(int c, char *str)
{
	if (str)
	{
		return (ft_isspace2(str));
	}
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

bool	ft_isword(int c)
{
	return (ft_isalpha(c) || ft_isalnum(c) || c == '$');
}

t_all	*getcore(void)
{
	static t_all	core;

	return (&core);
}
