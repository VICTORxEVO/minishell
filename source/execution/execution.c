


#include "minishell.h"



int main ()
{

        t_lx *lexer = get_core()->lexer;
		while(lexer)
		{
			printf("lx type -> %d, lx content ->\t%s\n", lexer->type, lexer->content);
			lexer = lexer->next;
		}
		clear(F_TMP);
}
