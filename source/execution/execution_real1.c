#include "minishell.h"

pid_t   forker(void (*child_fn)(void *), void *child_arg,
                    void (*parent_fn)(void *), void *parent_arg)
{
    pid_t   pid;

    if (!child_fn || !parent_fn)
        return(pexit(":forker: "FATAL_ERR"function pointer is NULL !", 1), -1);
    pid = fork();
    if (pid == -1)
    {
        pexit("fork", FORK_CODE);
        return (-1);
    }
    if (pid == 0)
        (child_fn(child_arg), exit(211));
    parent_fn(parent_arg);
    return (pid);
}
