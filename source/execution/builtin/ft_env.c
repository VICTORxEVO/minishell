/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysbai-jo <ysbai-jo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:45:27 by ysbai-jo          #+#    #+#             */
/*   Updated: 2024/12/22 11:45:28 by ysbai-jo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *var)
{
	t_env	*env;

	env = getcore()->env_list;
	while (env)
	{
		if (ft_strcmp(env->key, var) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	ft_env(void)
{
	t_env	*env;

	env = getcore()->env_list;
	if (env == NULL)
		return (1);
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
