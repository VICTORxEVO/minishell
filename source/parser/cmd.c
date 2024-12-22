/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:02:47 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 12:02:48 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_cmd_list(t_all *core)
{
	t_lx	*lexer;
	t_cmd	*cmd;

	lexer = core->lexer;
	core->cmd_count = core->pipe_count + 1;
	core->pids = galloc(sizeof(int *) * core->cmd_count);
	cmd = galloc(sizeof(t_cmd));
	while (lexer)
	{
		if (!cmd->scope)
		{
			cmd->scope = lexer;
			addtolist(cmd, "t_cmd", NULL);
		}
		if (lexer->type == PIPE)
		{
			lexer->prev->next = NULL;
			lexer->next->prev = NULL;
			cmd = galloc(sizeof(t_cmd));
		}
		lexer = lexer->next;
	}
	load_cmd(core->cmd);
}
