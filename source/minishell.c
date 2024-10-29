#include "minishell.h"

int main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	while (true)
	{
		reader_loop();
		parsing(env);

		t_lx *lexer = getcore()->lexer;
		t_var *list = getcore()->var_list;
		while(lexer)
		{
			printf("lx type -> %d, lx content ->\t%s\\0\n", lexer->type, lexer->content);
			lexer = lexer->next;
		}
		printf("---------------\n");
		while (list)
		{
        	printf ("list content is ->\t%s\\0\n", list->content);
        	list = list->next;
		}
		clear(F_TMP);
	}
	
	return 0;
}
