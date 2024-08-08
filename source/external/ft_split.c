/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 11:50:16 by ysbai-jo          #+#    #+#             */
/*   Updated: 2023/11/24 11:01:30 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_num(const char *s, const char x)
{
	int	wn;

	wn = 0;
	while (*s)
	{
		if (*s == x)
			s++;
		else
		{
			wn++;
			while (*s && *s != x)
				s++;
		}
	}
	return (wn);
}

static char	**mem_error(char **arr)
{
	int	r;

	r = 0;
	while (arr[r])
	{
		free(arr[r]);
		r++;
	}
	free(arr);
	return (NULL);
}

static char	*do_word(const char *s, const char x, int *q_resume)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	while (s[*q_resume] == x)
		(*q_resume)++;
	i = *q_resume;
	while (s[i] && s[i++] != x)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[*q_resume] && s[*q_resume] != x)
	{
		word[i] = s[*q_resume];
		(*q_resume)++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	int		q_res;
	int		wn;
	int		i;

	if (!s)
		return (NULL);
	wn = word_num(s, c);
	arr = malloc(sizeof(char *) * (wn + 1));
	if (!arr)
		return (NULL);
	arr[wn] = 0;
	q_res = 0;
	i = 0;
	while (i < wn)
	{
		arr[i] = do_word(s, c, &q_res);
		if (!(arr[i]))
			return (mem_error(arr));
		i++;
	}
	return (arr);
}
