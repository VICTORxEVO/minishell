


#include "minishell.h"


static int ft_export_check3(char *arg)
{
    size_t i;
    bool plus;

    if (!arg)
        return (0);
    if ((arg[0] != '_') && !ft_isalpha(arg[0]))
        return (0);
    i = 1;
    plus = false;
    while (arg[i]) 
    {
        if ((arg[i] == '=') || (arg[i] == '+' && arg[i + 1] == '=') || arg[i] == '+' && plus)
        {
            i++;
            plus = true;
            continue;
        }
        if (!ft_isdigit(arg[i]) && !ft_isalpha(arg[i]) && !(arg[i] == '_'))
            return (0);
        i++; 
    }
    return (1);
}

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
    
    env = getcore()->env_list;
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


static int ft_print_export_error2(char *cmd)
{
    printf("Eureka: export: %s: not a valid identifier\n", cmd);
    return (0);
} 

int    ft_export2(t_cmd *cmd)
{
    size_t i;
    int exit_status;

    i = 1;
    exit_status = 0;
    while (cmd->cmd[i])
    {
        if (ft_export_check3(cmd->cmd[i]))
            ft_add_export3(cmd->cmd[i]);
        else
            exit_status = ft_print_export_error2(cmd->cmd[i]);
        i++;
    }
    if (!cmd->cmd[1])
        ft_print_export2();
    return (0);
}


//TO DOs : 1 ->fix export [x]
//2 ->check all builtins
//3 -> setup todo for all builtins 

// //test builtin
// int main (int ac, char **av, char **env)
// {
//     t_all * core = get_core();
//     core->env_list = fill_env_list2(env);	

// 	char *cmd_str[]= {"export", "hello=yes", "hello","keyonly", "_=value", "_FINAL", NULL};

// 	t_cmd *cmd  = galloc(sizeof(t_cmd*));
// 	cmd->cmd  = cmd_str; 

// 	ft_export2(cmd);
//     ft_print_export2();
// 	// size_t len =  sizeof(cmd_str)  / sizeof(char *);

// 	// char **cmd_args = galloc(sizeof(char*) * len); 
// 	// size_t i = -1;
	
// 	// while (cmd_str[++i])
// 	// 	cmd_args[i] = cmd_str[i];

// 	// i = 0;
// 	// while (cmd_args[i])
// 	// 	printf("%s, ", cmd_args[i++]);
// 	// printf("\n");


// 	i = 0;
// 	while (cmd_args[i])
// 		printf("%s, ", cmd_args[i++]);
// 	printf("\n");
	
// 	// ft_print_export2();
//     // printf("adding export = ayoub\n");
//     // printf("adding export = aziz=great\n");
//     // printf("adding export = karim=\"\"\n");
//     // printf("===================\n");
//     // ft_add_export2("ayoub");
//     // ft_add_export2("aziz=great");
//     // ft_add_export2("karim=");
//     // ft_add_export2("said+=karim");
//     // printf("-----------exprot checks ------------\n");

//     // printf("%d\n" ,ft_export_check2("ayoub"));
//     // printf("%d\n" ,ft_export_check2("aziz=great"));
//     // printf("%d\n" ,ft_export_check2("karim="));
//     // printf("%d\n" ,ft_export_check2("_+=arim"));
//     // printf("===================\n");
//  // ft_print_export2();
// 	return (0);
// }

// Prototype of the function to be tested

// Test cases
void run_tests() {
    char *test_cases[] = {
        "VAR=value",
        "VAR=",
        "VAR",
        "=value",
        "VAR=value=extra",
        "VAR value",
        "VAR-value",
        NULL
    };

    int expected_results[] = {
        1, // "VAR=value" should be valid
        1, // "VAR=" should be valid
        0, // "VAR" should be invalid
        0, // "=value" should be invalid
        1, // "VAR=value=extra" should be valid
        0, // "VAR value" should be invalid
        0  // "VAR-value" should be invalid
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        int result = ft_export_check3(test_cases[i]);
        printf("Test case: \"%s\" - Expected: %d, Got: %d\n",
               test_cases[i], expected_results[i], result);
    }
}

int main() {
    run_tests();
    return 0;
}
