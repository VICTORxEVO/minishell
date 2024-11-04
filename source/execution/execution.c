


#include "minishell.h"


static int extract_key_value2(const char *arg, char **key, char **value) {
    char *equal_sign = ft_strchr(arg, '=');

    if (!equal_sign)
    {
        *key = ft_strdup(arg);
        *value = NULL;
        return (*key) ? 1 : 0;
    }
    *key = ft_strndup(arg, equal_sign - arg); 
    if (*(equal_sign + 1) == '\0')
        *value = ft_strdup("");
    else 
        *value = ft_strdup(equal_sign + 1);
    return (*key && *value) ? 1 : 0;
}


static int ft_add_export2(char *arg)
{
    t_env *env;
    char *key;
    char *value;
    char *tmp;
    char *equal_sign;

    env = get_core()->env_list;
    extract_key_value2(arg, &key, &value); 
    
    ft_setenv(key, value, 1); 
    return (1);
}

static void ft_print_export2()
{
    t_env *export;
    t_env *tmp;

    export = ft_copy_env();
    ft_sort_export(export);
    tmp = export;
    while (tmp)
    {
        if (tmp->value)
            printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
        else
            printf("declare -x %s\n", tmp->key); 
        tmp = tmp->next;
    }
} 


static t_env   *fill_env_list2(char *env[])
{
    t_env *env_list;
    t_env *head;
    char **key_val;
    t_ndx index;

    ft_bzero(&index, sizeof(t_ndx));
    while (env[index.i])
    {
        if (index.i == 0)
        {
            env_list = ft_calloc(1, sizeof(t_env));
            head = env_list;
        }
        else
        {
            while (env_list->next)
                env_list = env_list->next;
            env_list->next = ft_calloc(1, sizeof(t_env));
            env_list = env_list->next;
        }
        key_val = ft_split(env[index.i++], '=');
        env_list->key =  key_val[0];
        env_list->value = key_val[1];
    }
    return (head);
}

//test builtin
int main (int ac, char **av, char **env)
{

	// char *cmd_str[]= {"export", "hello=yes", "keyonly", "=value", "_FINAL", NULL};
	// size_t len =  sizeof(cmd_str)  / sizeof(char *);

	// char **cmd_args = galloc(sizeof(char*) * len); 
	// size_t i = -1;
	
	// while (cmd_str[++i])
	// 	cmd_args[i] = cmd_str[i];

	// i = 0;
	// while (cmd_args[i])
	// 	printf("%s, ", cmd_args[i++]);
	// printf("\n");

	// t_cmd *cmd  = galloc(sizeof(t_cmd*));	
	// cmd->cmd  = cmd_str; 
	// ft_export(cmd);

	t_all * core = get_core();
    core->env_list = fill_env_list2(env);	
	// ft_print_export2();
    printf("adding export = ayoub\n");
    printf("adding export = aziz=great\n");
    printf("adding export = karim=\"\"\n");
    printf("===================\n");
    ft_add_export2("ayoub");
    ft_add_export2("aziz=great");
    ft_add_export2("karim=");
    ft_add_export2("karim");

    printf("===================\n");
    ft_print_export2();
	return (0);
}
