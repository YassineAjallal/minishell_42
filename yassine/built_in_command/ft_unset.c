/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:04:30 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/07 02:13:57 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int search_env(char **env, char *to_search, int *variable_index)
{
	int i;
	int env_length;	

	i = 0;
	env_length = ft_strlen2d(env);	
	while(i < env_length)
	{
		if (ft_strncmp(env[i], to_search, ft_strlen(to_search)) == 0)
		{
			*variable_index = i;
			return (1);
		}
		i++;
	}
	return (0);
}

char **ft_unset(char *unset_var, char **old_env)
{
	int i;
	int variable_index;
	int env_length;
	char **new_env;
	int j;
	
	i = 0;
	j = 0;
	variable_index = 0;
	env_length = ft_strlen2d(old_env);	
	if (!search_env(old_env, unset_var, &variable_index))
		return (NULL);
	new_env = (char **)malloc(sizeof(char *) * env_length);
	while(j < env_length - 1)
	{
		if (i == variable_index)
		{
			free(old_env[variable_index]);
			i++;
		}
		new_env[j] = old_env[i];
		j++;
		i++;
	}
	new_env[j] = NULL;
	free(old_env);
	old_env = new_env;
	return (old_env);
}

// int main(int ac, char **av, char **env)
// {
// 	char **environ;
// 	int i;

// 	i = 0;
// 	environ = dup_env(env);
// 	while (i < ft_strlen2d(environ))
// 	{
// 		printf("%s\n",environ[i]);
// 		i++;
// 	}
// 	printf("\n------------------------------------------------------\n\n");
// 	i = 0;
// 	environ = ft_export(environ, "YASSINE=chdiid");
// 	while (i < ft_strlen2d(environ))
// 	{
// 		printf("%s\n",environ[i]);
// 		i++;
// 	}
// 	printf("\n------------------------------------------------------\n\n");
// 	i = 0;
// 	environ = ft_unset("YASSINE", environ);
// 	while (i < ft_strlen2d(environ))
// 	{
// 		printf("%s\n",environ[i]);
// 		i++;
// 	}
	
// }