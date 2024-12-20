



#include "minishell.h"


/**
 *          @details >FAILURE CASES< n,
 *           getwd() copies the error message associated with errno
            into the memory referenced by buf

     [EINVAL]           The size argument is zero.

     [ENOENT]           A component of the pathname no longer exists.

     [ENOMEM]           Insufficient memory is available.

     [ERANGE]           The size argument is greater than zero but smaller than the
                        length of the pathname plus 1.
 * 
*/

int     ft_pwd(t_cmd *cmd)
{
    char cwd[PATH_MAX];

    (void*)cmd;
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        pexit("pwd", 1, 0); 
        return (1);
    }
    printf("%s\n",cwd);
    return (0);
}
