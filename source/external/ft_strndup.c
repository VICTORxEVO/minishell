/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:31:45 by ael-moha          #+#    #+#             */
/*   Updated: 2024/11/27 15:36:22 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char *ft_strndup(const char *s, size_t n) {
    size_t len;
    char *dup;

    len = ft_strlen(s);
    if (n < len)
        len = n + 1;
    dup = (char *)galloc(len + 1);
    if (!dup)
        return NULL;
    ft_strlcpy(dup, s, len);
    dup[len] = '\0';
    return dup;
}