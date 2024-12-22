/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_touching.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:04:38 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 12:04:39 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calclen(char *str, int *quotes)
{
	t_ndx	index;
	char	quote;

	ft_bzero(&index, sizeof(t_ndx));
	index.l = ft_strlen(str);
	while (str[index.i])
	{
		if (str[index.i] == S_QUOTES || str[index.i] == D_QUOTES)
		{
			quotes[index.j++] = index.i;
			quote = str[index.i++];
			while (str[index.i] != quote)
				index.i++;
			quotes[index.j++] = index.i;
		}
		index.i++;
	}
	quotes[index.j] = -3070;
	return (index.l - index.j);
}

static char	*getnewstr(char *str)
{
	t_ndx	index;
	int		quotes[8192];
	char	*newstr;

	ft_bzero(&index, sizeof(t_ndx));
	index.l = calclen(str, quotes);
	newstr = galloc(sizeof(char) * (index.l + 1));
	while (str[index.i])
	{
		if (index.i == quotes[index.m])
		{
			index.m++;
			index.i++;
			continue ;
		}
		newstr[index.t++] = str[index.i++];
	}
	return (newstr);
}

static bool	havequotes(t_lx *lexer)
{
	if (lexer->type == WORD)
	{
		if (ft_strchr(lexer->content, S_QUOTES))
			return (true);
		else if (ft_strchr(lexer->content, D_QUOTES))
			return (true);
	}
	return (false);
}

void	final_touch(t_lx *lexer)
{
	char	*new_str;
	bool	flag;

	flag = 0;
	while (lexer)
	{
		if (lexer->type == WORD)
			flag = emptyword(lexer);
		if (flag == 0 && havequotes(lexer))
		{
			new_str = getnewstr(lexer->content);
			clear_1data(lexer->content);
			lexer->content = new_str;
		}
		lexer = lexer->next;
	}
}
