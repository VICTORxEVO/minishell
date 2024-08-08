/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:28:56 by ysbai-jo          #+#    #+#             */
/*   Updated: 2023/11/23 13:49:33 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	x;

	x = 0;
	if (size)
	{
		while (src[x] && x < (size - 1))
		{
			dest[x] = src[x];
			x++;
		}
		dest[x] = 0;
	}
	return (ft_strlen(src));
}
