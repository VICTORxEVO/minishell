/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:55:33 by ysbai-jo          #+#    #+#             */
/*   Updated: 2023/12/07 17:55:30 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l_len;
	size_t	q;

	if (*little == 0)
		return ((char *)big);
	l_len = ft_strlen(little);
	q = 0;
	while (q < len && big[q])
	{
		if (len - q >= l_len && !(ft_strncmp(&big[q], little, l_len)))
			return ((char *)&big[q]);
		++q;
	}
	return (NULL);
}
