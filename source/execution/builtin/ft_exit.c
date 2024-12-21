#include "minishell.h"


int    ft_exit()
{
    char **cmd;
    int exitcode;
    int i;

    cmd = getcore()->cmd->cmd;
    i = -1;
    exitcode = getcore()->exit_code;
    if (cmd[1] && cmd[2])
        return (pexit(": exit: too many arguments", 2, 0), 2);
    if (cmd[1])
    {
        while (cmd[1][++i])
        {
            if (!ft_isdigit((int)cmd[1][i]))
                return (pexit(ft_strjoin(ft_strjoin(": exit: ", cmd[1]), ": argument must be a number"), 2, 0), 2);
            if (i >= 4)
                return(pexit(EXIT_USAGE, 2, 0), 2);
        }
        exitcode = ft_atoi(cmd[1]);
        if (exitcode > 255)
            return(pexit(EXIT_USAGE, 2, 0), 2);
    }
    (clear(FREE_ALL), exit(exitcode));
}
