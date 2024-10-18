


#include "minishell.h"

char *get_home_directory() {
    char *home;
    
    home = getenv("HOME");
    if (home == NULL) {
        perror(": cd: HOME not set");
        return (NULL);
    }
    return home;
}

int lsh_cd(t_cmd *cmd) {
    if (cmd->cmd == NULL) {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    } else {
        // Handle special cases
        if (!cmd->cmd[1] || ft_strcmp(cmd->cmd[1], "~") == 0) {
            chdir(getenv("HOME"));
        } else if (ft_strcmp(cmd->cmd[1], "-") == 0) {
            // Logic to change to the previous directory can be added here
        } else {
            // Change to the specified directory
            if (chdir(cmd->cmd[1]) != 0) {
                perror("lsh"); // Print error if chdir fails
            }
        }
    }
    return 1; // Return success
}

// int ft_cd(t_cmd *cmd)
// {


//     return (1);
// }