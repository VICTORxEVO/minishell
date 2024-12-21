#include "minishell.h"

int main(int ac, char *av[], char *env[])
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
			continue;
		execution();
	}
}
