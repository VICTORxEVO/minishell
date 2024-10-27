/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:28:30 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/10/27 16:14:52 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ext_libs.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (n < 0)
	{
		while ((*str1 && *str2))
		{
			if (*str1 == *str2)
			{
				str1++;
				str2++;
			}
			else
				return (*(t_uc *)str1 - *(t_uc *)str2);
		}
	}
	while ((*str1 && *str2) && n--)
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
