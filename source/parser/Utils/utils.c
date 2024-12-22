/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:02:28 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 12:06:16 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	emptyword(t_lx *lexer)
{
	int	res;

	res = 0;
	if (lexer->prev && istoken(lexer->prev->type, NON_PIPE))
	{
		if (!lexer->content[0] || (lexer->content[0]
				&& checkspace_str(lexer->content)))
		{
			clear_1data(lexer->content);
			lexer->content = lexer->original_content;
			lexer->prev->type = AMBIG_RDRT;
			res = 1;
		}
	}
	else if (!lexer->content[0])
	{
		lexer->type = EMPTY_VAR;
		res = 1;
	}
	return (res);
}

bool	checkspace_str(char *str)
{
	int		i;
	char	quote;
	char	len;

	len = ft_strlen(str);
	i = -1;
	while (++i < len)
	{
		if (ft_isspace(str[i], NULL))
			return (true);
		if (str[i] == S_QUOTES || str[i] == D_QUOTES)
		{
			quote = str[i++];
			while (str[i] != quote)
				i++;
		}
	}
	return (false);
}

bool	needspliting(t_lx *lexer, t_lx *prev_lexer)
{
	if (lexer && lexer->type == WORD)
	{
		if (!prev_lexer || (prev_lexer && prev_lexer->type == WORD))
			return (checkspace_str(lexer->content));
	}
	return (false);
}
