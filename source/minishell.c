/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:15:35 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 12:15:36 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	fill_env_list(env);
	sighandler(0);
	while (true)
	{
		clear(FREE_TEMP);
		reader_loop();
		if (!parsing())
			continue ;
		execution();
	}
}
