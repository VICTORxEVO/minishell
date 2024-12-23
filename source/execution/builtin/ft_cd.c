/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:45:04 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 11:45:05 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_cwd(char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		pexit("cd: getcwd", 1, 0);
		return ;
	}
	ft_setenv("OLDPWD", strchrdup(oldpwd, NULL, CALLOC), 1);
	ft_setenv("PWD", strchrdup(cwd, NULL, CALLOC), 1);
}

static int	cha_dir(char *dir)
{
	char	oldpwd[PATH_MAX];

	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		return (pexit("cd: getcwd", 1, 0), 1);
	if (ft_strncmp(dir, "HOME", -1) == 0)
	{
		if (chdir(ft_getenv("HOME")))
			return (pexit(": cd: HOME not set", 1, 0), 1);
	}
	else
	{
		if (chdir(dir))
			return (pexit(ft_strjoin("cd: ", dir), 1, 0), 1);
	}
	update_env_cwd(oldpwd);
	return (0);
}

int	ft_cd(t_cmd *cmd)
{
	if (!cmd->cmd[1] || ft_strcmp(cmd->cmd[1], "~") == 0)
		return (cha_dir("HOME"));
	else if (cmd->cmd[1])
		return (cha_dir(cmd->cmd[1]));
	return (1);
}
