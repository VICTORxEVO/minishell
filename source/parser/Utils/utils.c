#include "minishell.h"

bool checkspace_str(char *str)
{
	int i;
	char quote;
	char len;

	len = ft_strlen(str);
	while (++i < len)
	{
		if (ft_isspace(str[i], NULL))
			return (true);
		if (str[i] == S_QUOTES || str[i] == D_QUOTES)
		{
			quote = str[i++];
			while (str[i] != quote)
				i++;
		}
	}
}

bool	needspliting(t_lx *lexer, t_lx *prev_lexer)
{
	if (lexer && lexer->type == WORD)
	{
		if (!prev_lexer || (prev_lexer && prev_lexer->type == WORD))
				return (checkspace_str(lexer->content));
	}
}


static char *get_current_dir(void)
{
    char cwd[PATH_MAX];
    char *dir_name;
    
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return ft_strdup("~");
        
    dir_name = ft_strrchr(cwd, '/');
    if (!dir_name || !*(dir_name + 1))
        return ft_strdup(cwd);
    return ft_strdup(dir_name + 1);
}

char *create_prompt(void)
{
    char *dir = get_current_dir();
    char *user = getenv("USER");
    char hostname[256]; // Buffer to store the hostname
    char *prompt;
    char *tmp1, *tmp2;

    if (!dir || !user)
        return NULL;

    // Get the hostname
    if (gethostname(hostname, sizeof(hostname)) != 0)
    {
        free(dir);
        return NULL;
    }

    // Build the prompt: [user@hostname] [directory] ➜ Eurika ✨
    tmp1 = ft_strjoin("\001\033[1;32m\002", user); // Green color
    tmp2 = ft_strjoin(tmp1, "@");
    clear_1data(tmp1);
    tmp1 = ft_strjoin(tmp2, hostname);
    clear_1data(tmp2);
    tmp2 = ft_strjoin(tmp1, "\001\033[0m\002 \001\033[1;34m\002"); // Reset color, then blue
    clear_1data(tmp1);
    tmp1 = ft_strjoin(tmp2, dir);
    clear_1data(tmp2);
    tmp2 = ft_strjoin(tmp1, "\001\033[0m\002 \001\033[1;36m\002➜ \001\033[0m\002"); // Reset color, arrow symbol
    clear_1data(tmp1);
    tmp1 = ft_strjoin(tmp2, "\001\033[1;33m\002 Eurika ✨ \001\033[0m\002"); // Yellow color for Eurika and symbols, then reset color
    clear_1data(tmp2);
    prompt = tmp1;
    clear_1data(dir);
    return prompt;
}

static char *get_token_type_str(int type)
{
    switch (type)
    {
        case HERE_DOC:
            return "HERE_DOC";
        case IN_RDRT:
            return "IN_RDRT";
        case OUT_RDRT_OW:
            return "OUT_RDRT_OW";
        case OUT_RDRT_APP:
            return "OUT_RDRT_APP";
        case WORD:
            return "WORD";
        case PIPE:
            return "PIPE";
        case TOKEN:
            return "TOKEN";
        default:
            return "UNKNOWN";
    }
}

void print_env(void)
{
    t_env *tmp = getcore()->env_list;
    t_env *counter = getcore()->env_list;
    int i = 1;
    size_t max_len = 0;

    if (!tmp)
    {
        printf("Environment list is empty\n");
        return;
    }
    // First pass: find longest key
    while (counter)
    {
        size_t len = strlen(counter->key);
        if (len > max_len)
            max_len = len;
        counter = counter->next;
    }
    // Add some padding
    max_len += 2;

    printf("\n=== Environment Variables List ===\n\n");
    while (tmp)
    {
        printf("[%d] %s", i++, BOLD_GREEN);
        printf("%-*s", (int)max_len, tmp->key);
        printf(END "= %s", tmp->value ? tmp->value : "(null)");
        printf("\n");
        tmp = tmp->next;
    }
    printf("\n=================================\n");
}

void print_lx(void)
{
    t_lx *lexer = getcore()->lexer;
    int i = 1;

    if (!lexer)
    {
        printf("Lexer list is empty\n");
        return;
    }
    printf("\n=== Lexer Token List ===\n\n");
    while (lexer)
    {
        printf("[%d] Token: %s", i++, BOLD_GREEN);
        printf("%-20s", lexer->content);
        printf(END " | Type: %s%s%s", BOLD_MAGENTA, get_token_type_str(lexer->type), END);
        printf("\n");
        lexer = lexer->next;
    }
    printf("\n=====================\n");
}