


#include "minishell.h"



int is_builtin(char *cmd)
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
    return (0);
}

int exec_builtin(t_cmd * cmd)
{
	if (ft_strcmp(cmd->cmd, "cmd") == 0)
		ft_cd(cmd);	

    return (0);
}

