#include "minishell.h"

int main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	fill_env_list(env);
	while (true)
	{
		reader_loop();
		parsing(env);
		clear(F_TMP);
	}
	
	return 0;
}
