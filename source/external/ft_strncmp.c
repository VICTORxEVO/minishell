/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:28:30 by ysbai-jo          #+#    #+#             */
/*   Updated: 2023/11/25 12:01:41 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	while ((*str1 || *str2) && n--)
	{
		if (*str1 == *str2)
		{
			str1++;
			str2++;
		}
		else
			return (*(t_uc *)str1 - *(t_uc *)str2);
	}
	return (0);
}
