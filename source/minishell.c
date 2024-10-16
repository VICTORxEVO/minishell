#include "minishell.h"

int main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	while (true)
	{
		reader_loop();
		parsing(env);

		t_lx *lexer = get_core()->lexer;
		while(lexer)
		{
			printf("lx type -> %d, lx content ->\t%s\n", lexer->type, lexer->content);
			lexer = lexer->next;
		}
		clear(F_TMP);
	}
	
	return 0;
}
