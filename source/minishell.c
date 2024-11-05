#include "minishell.h"

int main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	while (true)
	{
		reader_loop();
		parsing(env);
        // addoldhistory();
		// t_var *list = getcore()->var_list;
		// printf("---------------\n");
		// while (list)
		// {
        // 	printf ("list content is ->\t%s\\0\n", list->content);
        // 	list = list->next;
		// }
		clear(F_TMP);
	}
	
	return 0;
}
