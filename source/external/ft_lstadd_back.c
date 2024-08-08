/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:36:03 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/08/07 12:20:25 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	ft_lstadd_back(t_gc **lst, t_gc *new)
{
	t_gc	*tmp;

	if (!lst || !new)
		return ;
	tmp = *lst;
	if (*lst)
	{
		while ((tmp->next))
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}
