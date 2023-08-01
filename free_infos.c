/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_infos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 10:05:00 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/28 17:18:39 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_variables)
	{
		free(env->variables[i].name);
		free(env->variables[i].value);
		env->variables[i].name = NULL;
		env->variables[i].value = NULL;
		i++;
	}
	free (env->variables);
	env->variables = NULL;
	free (env);
	env = NULL;
}

void	free_infos(t_global_info *g_info)
{
	free_env(g_info->environ);
	free_env(g_info->export_env);
	ft_free2d(g_info->env_array);
	free(g_info);
	g_info = NULL;
}
