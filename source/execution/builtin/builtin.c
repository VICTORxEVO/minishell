/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:12:26 by ael-moha          #+#    #+#             */
/*   Updated: 2024/12/20 14:14:55 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"


void fill_builtins()
{
    t_builtin *builtins;
	
	builtins = galloc(sizeof(t_builtin) * 8);
    if (!builtins)
        return;
    builtins[0] = (t_builtin){strchrdup("echo", NULL, CALLOC), ft_echo};
    builtins[1] = (t_builtin){strchrdup("cd", NULL, CALLOC), ft_cd};
    builtins[2] = (t_builtin){strchrdup("pwd", NULL, CALLOC), ft_pwd};
    builtins[3] = (t_builtin){strchrdup("env", NULL, CALLOC), ft_env};
    builtins[4] = (t_builtin){strchrdup("export", NULL, CALLOC), ft_export};
    builtins[5] = (t_builtin){strchrdup("unset", NULL, CALLOC), ft_unset};
    builtins[6] = (t_builtin){strchrdup("exit", NULL, CALLOC), ft_exit};
    builtins[7] = (t_builtin){NULL, NULL};
    getcore()->builtins = builtins;
}

int is_builtin(char *cmd)
{
	size_t i;

	i = -1;
	while (getcore()->builtins[++i].name)
	{
       if (ft_strcmp(cmd, getcore()->builtins[++i].name) == 0)
            return (1);
	}
    return (0);
}

int exec_builtin(t_cmd *cmd)
{
	size_t i;

	i = -1;
    if (!cmd->cmd)
		return (1);
	while(getcore()->builtins[++i].name)
	{
        if (ft_strcmp(cmd->cmd[0], getcore()->builtins[++i].name) == 0)
        		return (getcore()->builtins[++i].func(cmd));
	}
    return (1);
}