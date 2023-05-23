/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:04:30 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/23 19:23:06 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int	search_env(t_env *env, char *to_search, int *var_pos)
{
	int	i;

	i = 0;
	while (i < env->nb_variables)
	{
		if (ft_strlen(to_search) == ft_strlen(env->variables[i].name))
		{	
			if (ft_strncmp(env->variables[i].name, to_search, \
			ft_strlen(to_search)) == 0)
			{
				*var_pos = i;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	delete_var(t_env *env, int var_pos)
{
	int	i;
	int	pos;

	i = 0;
	while (i < env->nb_variables)
	{
		if (i == var_pos)
		{
			while (i < env->nb_variables - 1)
			{
				free(env->variables[i].name);
				free(env->variables[i].value);
				pos = i + 1;
				env->variables[i].name = ft_strdup(env->variables[pos].name);
				env->variables[i].value = ft_strdup(env->variables[pos].value);
				i++;
			}
			free(env->variables[i].name);
			free(env->variables[i].value);
			env->nb_variables--;
			break ;
		}
		i++;
	}
}

int	unset_one_var(char *unset_var, t_env *env)
{
	int	i;
	int	var_pos;

	i = 0;
	if (!valid_name(unset_var))
	{
		ft_putstr_fd("minishell: not a valid identifier\n", 2);
		return (0);
	}
	if (!search_env(env, unset_var, &var_pos))
		return (0);
	delete_var(env, var_pos);
	return (1);
}

int	ft_unset(t_command *cmd)
{
	int	i;
	int	error_count;

	error_count = 0;
	i = 1;
	while (cmd->cmd_parameter[i])
	{
		if (!unset_one_var(cmd->cmd_parameter[i], cmd->g_info->environ))
			error_count++;
		i++;
	}
	if (cmd->g_info->env_array)
		ft_free2d(cmd->g_info->env_array);
	cmd->g_info->env_array = convert_env_array(cmd->g_info->environ);
	if (error_count > 0)
		cmd->g_info->exit_code = 1;
	else
		cmd->g_info->exit_code = 0;
	return (1);
}
