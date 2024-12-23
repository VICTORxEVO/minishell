/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:45:02 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 11:45:03 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", -1) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd)
{
	if (!cmd->cmd)
		return (0);
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (ft_cd(cmd));
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (ft_env());
	if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (ft_export(cmd));
	if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (ft_unset(cmd));
	if (ft_strncmp(cmd->cmd[0], "exit", -1) == 0)
		return (ft_exit(cmd->cmd));
	return (0);
}
