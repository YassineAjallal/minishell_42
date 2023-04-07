/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 04:45:32 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/07 02:03:42 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

char **dup_env(char **env)
{
	char **environ;
	int env_length;
	int i;

	env_length = ft_strlen2d(env);
	environ = malloc(sizeof(char *) * (env_length + 1));
	i = 0;
	if (!environ)
		return (NULL);
	while(i < env_length)
	{
		environ[i] = ft_strdup(env[i]);
		i++;
	}
	environ[i] = NULL;
	return (environ);
}

char **ft_export(char **old_env, char *env_var)
{
	int env_length;
	char **new_env;
	int i;

	i = 0;
	env_length = ft_strlen2d(old_env);
	if (!old_env)
		return (NULL);
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
	old_env = new_env;
	return (old_env);
}
