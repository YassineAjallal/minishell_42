/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 04:45:32 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/09 00:45:14 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int check_env_var(char *env_var)
{
	char **split_var;

	split_var = ft_split(env_var, '=');
	if (ft_strlen2d(split_var) == 1)
	{
		free(split_var[0]);
		ft_free2d(split_var);
		return (0);
	}
	return (1);
}

char **ft_export(char **old_env, char *env_var)
{
	int env_length;
	char **new_env;
	int i;

	i = 0;
	env_length = ft_strlen2d(old_env);
	if (!env_var)
		return (NULL);
	// if (!check_env_var(env_var))
	// {
	// 	free(env_var);
	// 	return (NULL);
	// }
	// if (!old_env)
	// 	return (NULL);
	new_env = malloc(sizeof(char *) * (env_length + 2));
	if (!new_env)
		return (NULL);
	while(i < env_length)
	{
		new_env[i] = old_env[i];
		i++;
	}
	new_env[i] = ft_strdup(env_var);
	new_env[++i] = NULL;
	free(old_env);
	// free(env_var);
	old_env = new_env;
	return (old_env);
}
