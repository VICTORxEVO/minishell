


#include "minishell.h"

void test_export(void)
{
    printf("\n=== Testing Export ===\n");

    // Setup test environment
    t_cmd test_cmd;
    char *env[] = {"PATH=/usr/bin", "HOME=/home/user", NULL};
    fill_env_list(env);

    // Test cases
    char *test_cases[][10] = {
        {"export", "TEST=value", NULL},             // Basic export
        {"export", "EMPTY=", NULL},                 // Empty value
        {"export", "NO_VALUE", NULL},               // No value
        {"export", "APPEND=1", "APPEND+=2", NULL},  // Append value
        {"export", "INVALID=@#$", NULL},           // Invalid value
        {"export", NULL},                          // Print all exports
        {NULL}
    };

    // Run tests
    for (int i = 0; test_cases[i][0] != NULL; i++)
    {
        printf("\nTest case %d: ", i + 1);
        test_cmd.cmd = test_cases[i];
        
        // Print test command
        for (int j = 0; test_cmd.cmd[j] != NULL; j++)
            printf("%s ", test_cmd.cmd[j]);
        printf("\n");

        // Execute export
        ft_export(&test_cmd);

        // Verify result
        if (test_cmd.cmd[1] != NULL)
        {
            char *key = strchrdup(test_cmd.cmd[1], ft_strchr(test_cmd.cmd[1], '='), CALLOC);
            char *value = ft_getenv(key);
            printf("Result: %s=%s\n", key, value ? value : "(null)");
        }
    }
    clear(FREE_ALL);
}

int main(void)
{
    test_export();
    return 0;
}
