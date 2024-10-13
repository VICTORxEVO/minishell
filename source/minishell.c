#include "minishell.h"

int main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	parsing(env);

	t_all *core = get_core();
	for(t_lx *lx = core->lexer; lx; lx = lx->next)
		printf("lx type -> %C\tvalue ->%s\n", lx->type, lx->content);
	
	return 0;
}
