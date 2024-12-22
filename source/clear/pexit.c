/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:44:29 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 11:44:30 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pexit(char *msg, short int exit_code, bool exit_flg)
{
	ft_putstr_fd(PRGM_NAME, 2);
	if (msg[0] == ':')
		(ft_putstr_fd(msg, 2), ft_putstr_fd("\n", 2));
	else
		(ft_putstr_fd(": ", 2), perror(msg));
	if (exit_code > 0)
		getcore()->error_flag = true;
	if (exit_flg)
	{
		clear(FREE_ALL);
		exit(exit_code);
	}
	getcore()->exit_code = (unsigned char)exit_code;
}
