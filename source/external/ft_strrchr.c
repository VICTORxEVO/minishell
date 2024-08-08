/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:55:37 by ysbai-jo          #+#    #+#             */
/*   Updated: 2023/11/24 11:16:17 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	b;

	b = ft_strlen(str);
	while (b >= 0)
	{
		if (str[b] == (unsigned char)c)
			return ((char *)&str[b]);
		b--;
	}
	return (NULL);
}
