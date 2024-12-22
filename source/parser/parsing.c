/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:07:21 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 12:07:22 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_quotes(char *line)
{
	long long	i;
	char		quote;

	i = -1;
	while (line[++i])
	{
		if (line[i] == S_QUOTES || line[i] == D_QUOTES)
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] != quote)
				return (pexit(DQ_ERR, 1, 0), false);
		}
	}
	return (true);
}

void	reader_loop(void)
{
	char	*line;

	while (true)
	{
		line = readline("Eurika ✨➜ ");
		if (!line)
			(clear(FREE_ALL), exit(getcore()->exit_code));
		if (line[0] == 0 || ft_isspace(0, line))
		{
			if (line)
				free(line);
			continue ;
		}
		getcore()->in_line = line;
		(gc_add_node(line), add_history(line));
		break ;
	}
}

bool	parsing(void)
{
	t_all	*core;

	core = getcore();
	if (!check_quotes(core->in_line) || !lexing(core->in_line))
		return (false);
	if (needexpand(core->in_line, NULL))
		expanding(core->lexer);
	final_touch(core->lexer);
	if (open_allhd(core->lexer) == 1)
		return (false);
	load_cmd_list(core);
	return (true);
}
