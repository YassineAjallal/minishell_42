/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:28:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/09 00:39:30 by yajallal         ###   ########.fr       */
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

void ft_env(char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}