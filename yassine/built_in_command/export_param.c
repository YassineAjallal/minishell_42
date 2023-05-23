/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:14:36 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/23 18:53:24 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int	already_exist(char *name, t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_variables)
	{
		if (ft_strcmp(name, env->variables[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	valid_name(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]))
			return (0);
		i++;
	}
	return (1);
}

int	var_one_eq(char *eq_split, char *param, t_variable new_var, \
t_global_info *g_info)
{
	int	error_count;

	error_count = 0;
	if (valid_name(eq_split))
	{
		new_var.name = ft_strdup(eq_split);
		if (ft_strchr(param, '='))
		{
			new_var.value = ft_strdup("");
			export_normal_var(new_var, g_info);
		}
		else
		{
			new_var.value = NULL;
			fill_var_list(new_var, g_info->export_env);
		}
	}
	else
	{
		ft_putstr_fd("minishell: not a valid identifier\n", 2);
		error_count++;
	}
	return (error_count);
}

int	var_more_eq(char *eq_split, char *param, t_variable new_var, \
t_global_info *g_info)
{
	int	equal_pos;
	int	error_count;

	error_count = 0;
	if (valid_name(eq_split))
	{		
		equal_pos = get_until_equal(param);
		new_var.name = ft_substr(param, 0, equal_pos);
		new_var.value = ft_substr(param, equal_pos + 1, ft_strlen(param));
		export_normal_var(new_var, g_info);
	}
	else
	{
		ft_putstr_fd("minishell: not a valid identifier\n", 2);
		error_count++;
	}
	return (error_count);
}

int	ft_export(t_command *cmd)
{
	char		**equal_split;
	int			error_count;
	t_variable	new_var;
	int			i;

	i = 1;
	error_count = 0;
	new_var.name = ft_strdup("");
	new_var.value = ft_strdup("");
	while (cmd->cmd_parameter[i])
	{
		equal_split = ft_split(cmd->cmd_parameter[i], '=');
		if (ft_strlen2d(equal_split) == 1)
			error_count += var_one_eq(equal_split[0], cmd->cmd_parameter[i], \
			new_var, cmd->g_info);
		else if (ft_strlen2d(equal_split) > 1)
			error_count += var_more_eq(equal_split[0], cmd->cmd_parameter[i], \
			new_var, cmd->g_info);
		else
			error_count++;
		i++;
	}
	if (error_count > 0)
		cmd->g_info->exit_code = 1;
	else
		cmd->g_info->exit_code = 0;
	return (error_count);
}
