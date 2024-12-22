#include "minishell.h"


int    ft_exit(char **cmd)
{
    int i;

    i = -1;
    if (cmd[1] && cmd[2])
        return (pexit(": exit: too many arguments", 2, EXIT), 2);
    if (cmd[1])
    {
        if (cmd[1][0] == '-')
            ++i;
        while (cmd[1][++i])
        {
            if (!ft_isdigit((int)cmd[1][i]))
                return (pexit(ft_strjoin(ft_strjoin(": exit: ", cmd[1]), ": argument must be a number"), 2, EXIT), 2); 
        }
        getcore()->exit_code = ft_atoi(cmd[1]);
    }
    if (getcore()->subshell == false)
        printf("exit\n");
    (clear(FREE_ALL), exit(getcore()->exit_code));
}
