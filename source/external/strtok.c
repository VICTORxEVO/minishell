#include <ext_libs.h>

char *strtok(char *str, const char *delim)
{
    static char *lasts;
    char *start;

    if (str == NULL)
        str = lasts;
    while (*str && ft_strchr(delim, *str))
        str++;
    if (*str == 0)
        return (NULL);
    start = str;
    while (*str && !ft_strchr(delim, *str))
        str++;
    if (*str == 0)
        lasts = NULL;
    else
        *str++ = 0;
    return (start);
}