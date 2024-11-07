#include "minishell.h"

int main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	while (true)
	{
		reader_loop();
		parsing(env);
		clear(F_TMP);
	}
	
	return 0;
}
