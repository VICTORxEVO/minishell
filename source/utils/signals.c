/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 12:11:58 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 12:11:59 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler_hd(int sig)
{
	(void)sig;
	clear(FREE_ALL);
	close(getcore()->gnl_fd);
	exit(SIG_BASE_CODE + sig);
}

static void	sigint_handler(int sig)
{
	if (waitpid(-1, NULL, WNOHANG) == -1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	getcore()->exit_code = SIG_BASE_CODE + sig;
	(void)sig;
}

void	sighandler(bool mode)
{
	struct sigaction	s_int;
	struct sigaction	s_quit;

	ft_bzero(&s_int, sizeof(s_int));
	ft_bzero(&s_quit, sizeof(s_quit));
	sigemptyset(&s_int.sa_mask);
	sigemptyset(&s_quit.sa_mask);
	if (mode == SG_HD_MODE)
		s_int.sa_handler = sigint_handler_hd;
	else
		s_int.sa_handler = sigint_handler;
	s_int.sa_flags = SA_RESTART;
	s_quit.sa_handler = SIG_IGN;
	s_quit.sa_flags = 0;
	if (sigaction(SIGINT, &s_int, NULL) == -1 || sigaction(SIGQUIT, &s_quit,
			NULL) == -1)
		pexit("sigaction()", EXIT_FAILURE, 1);
}
