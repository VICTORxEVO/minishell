#include "minishell.h"

t_all   *get_core(void)
{
    static t_all core;

    return (&core);
}