/**
 * @details this header adds external libs like stdlib and also  same of libft functions
 */
#ifndef EXT_LIBS_H
# define EXT_LIBS_H


# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <assert.h>
# include <sys/wait.h>
# include <signal.h>


typedef unsigned char	t_uc; //just a macro that i used in libft to avoid long line on norminette ;)

int			ft_toupper(int x);
int			ft_tolower(int x);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strrchr(const char *str, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_strncmp(const char *str1, const char *str2, ssize_t n);
int         ft_strcmp(const char *s1, const char *s2);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strchr(const char *str, int c);
char		**ft_split(const char *s, char c);
void		*ft_memset(void *dest, int c, size_t count);
void		*ft_memmove(void *dest, const void *src, size_t count);
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_memcmp(const void *str1, const void *str2, size_t n);
void		*ft_memchr(const void *str, int c, size_t n);
char		*ft_itoa(int n);
int			ft_isdigit(int x);
int			ft_isascii(int x);
int			ft_isalpha(int x);
int			ft_isalnum(int x);
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
int			ft_isprint(int c);
void        *ft_calloc(size_t n, size_t size);
void        ft_bzero(void *s, size_t n);
char        *ft_strtrim(char const *s1, char const *set);


#endif