

#include "minishell.h"

static size_t is_flag(char *prompt, int * flag_found)
{
    size_t i;

    i = 0;
    if (ft_strncmp(prompt, "-n",2) == 0)
    {
        *flag_found = 1;
        i += 2;
        while (prompt[i] == 'n')
            i++;
        if (prompt[i] != 0)
        {
            *flag_found = 0;
            return (0);
        }
    }
    return (i);
}

int    ft_echo(t_cmd *cmd)
{
    size_t i;
    int flag_found;

    i = 1;
    flag_found = 0;
    while (cmd->cmd[i] && is_flag(cmd->cmd[i], &flag_found))
        i++;
    while (cmd->cmd[i])
    {
        printf("%s", cmd->cmd[i]);
        if (cmd->cmd[i + 1])
            printf(" ");
        i++;
    }
    if (!flag_found)
        printf("\n"); 
    return (0);
}
