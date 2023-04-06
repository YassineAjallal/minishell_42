/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 04:45:32 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/06 01:19:59 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int dup_env(char **env)
{
	t_env *environ;
	int env_length;
	char **split_env_var;
	int i;
	int j;

	env_length = ft_strlen2d(env);
	environ = malloc(sizeof(t_env) * env_length);
	i = 0;
	if (!environ)
		return (0);
	while(i < env_length)
	{
		split_env_var = ft_split(env[i], '=');
		environ[i].name = split_env_var[0];
		environ[i].value = ft_strdup(env[i] + ft_strlen(split_env_var[0]) + 1);
		j = 1;
		while (split_env_var[j])
		{
			free(split_env_var[j]);
			j++;
		}
		free(split_env_var);
		i++;
	}
	i = 0;
	while(i < env_length)
	{
		printf("%s = %s\n", environ[i].name, environ[i].value);
		i++;
	}
	return (1);
}
// int ft_export(char **env, char *name, char *value)
// {
	
// }
int main(int argc, char const *argv[], char **env)
{
	dup_env(env);
	return 0;
}
