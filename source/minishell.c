#include "minishell.h"

int main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	parsing(env);

	t_lx *lexer = get_core()->lexer;
	while(lexer)
	{
		printf("lx type ->%d, lx content ->%s\n", lexer->type, lexer->content);
		lexer = lexer->next;
	}
	
	return 0;
}
