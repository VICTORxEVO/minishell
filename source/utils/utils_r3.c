/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_r3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:15:12 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 15:58:09 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*getlastnode(void *list, char *list_type)
{
	if (list && !ft_strncmp(list_type, "t_lx", -1))
	{
		while (((t_lx *)list)->next)
			list = ((t_lx *)list)->next;
	}
	else if (list && !ft_strncmp(list_type, "t_env", -1))
	{
		while (((t_env *)list)->next)
			list = ((t_env *)list)->next;
	}
	return (list);
}
