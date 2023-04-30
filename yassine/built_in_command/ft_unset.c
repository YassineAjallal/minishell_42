/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:04:30 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/28 18:38:19 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int search_env(t_env *env, char *to_search, int *var_pos)
{
	int i;

	i = 0;
	while(i < env->nb_variables)
	{
		if (ft_strlen(to_search) == ft_strlen(env->variables[i].name))
		{	
			if (ft_strncmp(env->variables[i].name, to_search, ft_strlen(to_search)) == 0)
			{
				*var_pos = i;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_unset(char *unset_var, t_env *old_env)
{
	int i;
	int var_pos;

	i = 0;
	if (!search_env(old_env, unset_var, &var_pos))
		return (0);
	while (i < old_env->nb_variables)
	{
		if (i == var_pos)
		{
			while (i < old_env->nb_variables - 1)
			{
				free(old_env->variables[i].name);
				free(old_env->variables[i].value);
				old_env->variables[i].name = ft_strdup(old_env->variables[i + 1].name);
				old_env->variables[i].value = ft_strdup(old_env->variables[i + 1].value);
				i++;
			}
			free(old_env->variables[i].name);
			free(old_env->variables[i].value);
			old_env->nb_variables--;
			break;
		}
		i++;
	}
	return (1);
}
