#include "minishell.h"

int main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	fill_env_list(env);
	while (true)
	{
		reader_loop();
		parsing();
		clear(FREE_TEMP);
	}
}
