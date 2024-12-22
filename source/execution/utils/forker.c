/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:54:36 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 11:54:37 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	forker(void (*child_fn)(void *), void *child_arg,
		void (*parent_fn)(void *, pid_t), void *parent_arg)
{
	pid_t	pid;

	if (!child_fn || !parent_fn)
		return (pexit(":forker: " FATAL_ERR "function pointer is NULL !", 1,
				EXIT), -1);
	pid = fork();
	if (pid == -1)
	{
		pexit("fork", FORK_CODE, EXIT);
		return (-1);
	}
	if (pid == 0)
		(child_fn(child_arg), exit(211));
	if (parent_fn)
		parent_fn(parent_arg, pid);
	return (pid);
}
