/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:22:56 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/08/07 12:21:00 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_gc	*ft_lstnew(void *content)
{
	t_gc	*new;

	new = malloc(sizeof(t_gc));
	if (!new)
		return (NULL);
	new->data = content;
	new->next = NULL;
	return (new);
}
