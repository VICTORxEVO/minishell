/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 21:31:45 by ael-moha          #+#    #+#             */
/*   Updated: 2024/11/03 21:52:19 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ext_libs.h"
#include "gc.h"

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