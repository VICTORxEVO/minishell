/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:45:16 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 11:45:17 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	is_flag(char *prompt, int *flag_found)
{
	size_t	i;
	int		old_flag;

	i = 0;
	old_flag = *flag_found;
	if (ft_strncmp(prompt, "-n", 2) == 0)
	{
		*flag_found = 1;
		i += 2;
		while (prompt[i] == 'n')
			i++;
		if (prompt[i] != 0)
		{
			if (!old_flag)
				*flag_found = 0;
			return (0);
		}
	}
	return (i);
}

int	ft_echo(t_cmd *cmd)
{
	size_t	i;
	int		flag_found;

	i = 1;
	flag_found = 0;
	while (cmd->cmd[i] && is_flag(cmd->cmd[i], &flag_found))
		i++;
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], 1);
		if (cmd->cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!flag_found)
		ft_putstr_fd("\n", 1);
	return (0);
}
