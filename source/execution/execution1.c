/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:55:00 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 11:55:01 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	gen_newpip(int *pip, t_cmd *cmd)
{
	if (pipe(pip) < 0)
		return (pexit("pipe", PIPE_CODE, 0), 1);
	cmd->ofd = pip[WRITE_END];
	cmd->unsed_fd = pip[READ_END];
	return (0);
}

void	wait_childs(pid_t *pid)
{
	int	i;
	int	status;

	i = -1;
	while (++i < (int)getcore()->cmd_count)
		waitpid(pid[i], &status, 0);
	getcore()->exit_code = WEXITSTATUS(status);
}

void	exec_cmdparent(void *data, pid_t pid)
{
	int	status;
	int	*i;
	int	signal;

	signal = 0;
	i = (int *)data;
	if (i)
	{
		getcore()->pids[*i] = pid;
		if (*i + 1 == (int)getcore()->cmd_count)
			wait_childs(getcore()->pids);
		return ;
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status) + 128;
		if (WTERMSIG(status) == SIGSEGV)
			ft_putstr_fd("Segmentation fault (core dumped)\n", 2);
	}
	getcore()->exit_code = WEXITSTATUS(status) + signal;
}

void	exec_cmdchild(void *data)
{
	t_cmd	*cmd;
	char	*cmdpath;

	getcore()->exit_code = 0;
	getcore()->subshell = true;
	cmd = (t_cmd *)data;
	if (prepare_ifof(cmd) == 0)
	{
		if (cmd->cmd && !is_builtin(cmd->cmd[0]))
		{
			cmdpath = getcmdpath(cmd->cmd[0]);
			if (cmdpath)
			{
				execve(cmdpath, cmd->cmd, getcore()->env);
				pexit("execve", 1, 0);
			}
		}
	}
	exec_builtin(cmd);
	(close(STDIN_FILENO), close(STDOUT_FILENO));
	(clear(FREE_ALL), exit(getcore()->exit_code));
}
