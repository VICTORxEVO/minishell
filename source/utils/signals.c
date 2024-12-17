

#include "minishell.h"

void sigquit_handler_ignore(int sig)
{
	(void)sig;
}

void	sigint_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void sighandler()
{
	struct sigaction act_int;
	struct sigaction act_quit;

	act_int.sa_sigaction = sigint_handler;
	act_quit.sa_sigaction = sigquit_handler_ignore;
	sigemptyset(&act_int.sa_mask);
	sigemptyset(&act_quit.sa_mask);
	act_int.sa_flags = SA_SIGINFO;
	act_quit.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &act_int, NULL) == -1)
		pexit("sigaction()", EXIT_FAILURE, 1);
	if (sigaction(SIGQUIT, &act_quit, NULL) == -1)
		pexit("sigaction()", EXIT_FAILURE, 1);
}
