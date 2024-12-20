#include "minishell.h"


int    ft_exit(t_cmd *cmd)
{
    char **cmmd;
    int exitcode;
    int i;

    cmmd = cmd->cmd;
    i = -1;
    exitcode = getcore()->exit_code;
    if (cmmd[1] && cmmd[2])
        return (pexit(": exit: too many arguments", 2, 0), 2);
    if (cmmd[1])
    {
        while (cmmd[1][++i])
        {
            if (!ft_isdigit((int)cmmd[1][i]))
                return (pexit(ft_strjoin(ft_strjoin(": exit: ", cmmd[1]), ": argument must be a number"), 2, 0), 2);
            if (i >= 4)
                return(pexit(EXIT_USAGE, 2, 0), 2);
        }
        exitcode = ft_atoi(cmmd[1]);
        if (exitcode > 255)
            return(pexit(EXIT_USAGE, 2, 0), 2);
    }
    (clear(FREE_ALL), exit(exitcode));
}
