


#include "minishell.h"

char *get_home_directory() {
    char *home;
    
    home = getenv("HOME");
    if (home == NULL) {
        perror("cd: HOME not set\n");
        return (NULL);
    }
    return (home);
}

char  *update_env_cwd(char *oldpwd) {
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("minishell: cd: getcwd");
        return;
    }
    setenv("OLDPWD", oldpwd, 1);
    setenv("PWD", cwd, 1);
}


int ft_cd(t_cmd * cmd)
{

    char cwd[PATH_MAX];
    char *owd;
    
    if (!getcwd(cwd, sizeof(cwd)))
        return (-1);
    if (!cmd->cmd[1] || ft_strcmp(cmd->cmd[1], "~") == 0) {
    {
        update_env_cwd(cwd);
        chdir(ft_getenv("HOME"));
    }
    } else if (ft_strcmp(cmd->cmd[1], "-") == 0)
    {
        if (chdir(owd) == 0)
            owd = update_env_cwd(cwd);
        else
        {
            //to add, program name instead of "bash"
            printf("bash: cd: %s: No such file or directory\n", owd);
        }
    }
    else if (ft_strcmp(cmd->cmd[1], "."))
    {

    }
    else if (ft_strcmp(cmd->cmd[1], ".."))
    {
        if (chdir(cmd->cmd[1]) != 0) {
            perror("error"); // Print error if chdir fails
        }
    }
    return (1); 
}
