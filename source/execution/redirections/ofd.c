/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ofd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:49:10 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 11:53:22 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ofd(char *filename, char mode)
{
	int	fd;

	if (mode == OUT_RDRT_OW)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd < 0)
		pexit(filename, GNRL_CODE, 0);
	return (fd);
}
