/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_r4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:15:02 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 12:16:14 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			pexit("malloc", MALLOC_CODE, EXIT);
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

char	*strchrdup(const char *str, char *delimit, bool type)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (&str[i] == delimit && type == CALLOC)
			return (ft_csubstr(str, 0, i));
		else if (&str[i] == delimit && type == GALLOC)
			return (ft_substr(str, 0, i));
	}
	if (type == CALLOC)
		return (ft_csubstr(str, 0, i));
	return (ft_substr(str, 0, i));
}
