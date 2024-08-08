#ifndef MINISHELL_H
# define MINISHELL_H


# include "libft.h"
# include "ext_libs.h"
# include "gc.h"

struct s_core t_core;

typedef struct s_lx
{
    
}   t_lx;






typedef struct s_core
{
    
    t_core  **scopes;
    t_gc    *gc_tmp;
    t_gc    *gc_perm;
}   t_core;


































#endif
