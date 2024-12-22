/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:45:56 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 18:33:51 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_export(void)
{
	t_env	*export;
	t_env	*tmp;

	export = ft_copy_env();
	ft_sort_export(export);
	tmp = export;
	while (tmp)
	{
		if (tmp->value)
			printf("export %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
	return (0);
}
