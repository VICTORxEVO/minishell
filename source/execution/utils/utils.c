/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:54:29 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 11:54:30 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_allhd(t_lx *lexer)
{
	if (getcore()->hd_mode == false)
		return ;
	while (lexer)
	{
		if (lexer->type == HERE_DOC_FD)
			close(atoi(lexer->next->content));
		lexer = lexer->next;
	}
}

bool	backup_fd(int *fd)
{
	if (fd[2] == 0)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
		if (fd[0] < 0 || fd[1] < 0)
			return (pexit("dup", 1, 0), 0);
		return (0);
	}
	if (dup2(fd[0], STDIN_FILENO) < 0 || dup2(fd[1], STDOUT_FILENO) < 0)
		return (pexit("dup2", DUP2_CODE, 0), 0);
	if (close(fd[0]) < 0 || close(fd[1]) < 0)
		return (pexit("close", CLOSE_CODE, 0), 0);
	return (0);
}

static char	check_path_in_core(char *cmd, char *not_found, char *perm_denied,
		char **returnpath)
{
	char		**path;
	int			i;
	struct stat	path_stat;

	path = getcore()->path;
	i = -1;
	while (path && path[++i])
	{
		*returnpath = ft_strjoin(path[i], cmd);
		if (stat(*returnpath, &path_stat) == 0 && !S_ISDIR(path_stat.st_mode))
		{
			if (!(path_stat.st_mode & S_IXUSR))
				return (pexit(perm_denied, PERM_DENIED_CODE, 0), 2);
			return (0);
		}
	}
	return (pexit(not_found, CMD_NOTFOUND_CODE, 0), 2);
}

static char	check_absolute_or_relative_path(char *path, char *perm_denied)
{
	struct stat	path_stat;
	char		*isdir;
	char		*no_file;

	no_file = ft_strjoin(ft_strjoin(": ", path),
			": No such file or directory !");
	isdir = ft_strjoin(ft_strjoin(": ", path), CMD_DIR);
	if (path[0] == '/' || path[0] == '.' || !getcore()->path)
	{
		if (stat(path, &path_stat) < 0)
			return (pexit(no_file, CMD_NOTFOUND_CODE, 0), 1);
		if (S_ISDIR(path_stat.st_mode))
			return (pexit(isdir, PERM_DENIED_CODE, 0), 2);
		if (!(path_stat.st_mode & S_IXUSR))
			return (pexit(perm_denied, PERM_DENIED_CODE, 0), 2);
		return (0);
	}
	return (-1);
}

char	*getcmdpath(char *cmd)
{
	char	res;
	char	*not_found;
	char	*perm_denied;
	char	*fullpath;

	not_found = ft_strjoin(ft_strjoin(": ", cmd), CMD_NOTFOUND);
	perm_denied = ft_strjoin(ft_strjoin(": ", cmd), PERM_DENIED);
	res = check_absolute_or_relative_path(cmd, perm_denied);
	if (res == 0)
		return (cmd);
	if (res > 0)
		return (NULL);
	if (res == -1)
	{
		res = check_path_in_core(cmd, not_found, perm_denied, &fullpath);
		if (res == 0)
			return (fullpath);
		if (res > 0)
			return (NULL);
	}
	return (NULL);
}
