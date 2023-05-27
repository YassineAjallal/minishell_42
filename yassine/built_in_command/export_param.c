/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:14:36 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 19:02:49 by yajallal         ###   ########.fr       */
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
	i++;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	var_more_eq(char *eq_split, char *param, t_global_info *g_info)
{
	int			equal_pos;
	t_variable	new_var;

	if (valid_name(eq_split) && param[0] != '=')
	{		
		equal_pos = get_until_equal(param);
		new_var.name = env_substr(param, 0, equal_pos);
		if (!ft_strchr(param, '='))
		{
			new_var.value = NULL;
			fill_var_list(new_var, g_info->export_env);
		}
		else
		{
			new_var.value = env_substr(param, equal_pos + 1, ft_strlen(param));
			export_normal_var(new_var, g_info);
		}
		free(new_var.name);
		free(new_var.value);
	}
	else
		return (ft_putstr_fd("minishell: not a valid identifier\n", 2), 1);
	return (0);
}

int	ft_export(t_command *cmd)
{
	char		**equal_split;
	int			error_count;
	int			i;

	i = 0;
	error_count = 0;
	while (cmd->cmd_parameter[++i])
	{
		equal_split = ft_split(cmd->cmd_parameter[i], '=');
		if (ft_strlen2d(equal_split) >= 1)
			error_count += var_more_eq(equal_split[0], \
			cmd->cmd_parameter[i], cmd->g_info);
		else
		{
			ft_putstr_fd("minishell: not a valid identifier\n", 2);
			error_count++;
		}
	}
	if (error_count > 0)
		cmd->g_info->exit_code = 1;
	else
		cmd->g_info->exit_code = 0;
	return (error_count);
	// protect ft_malloc
}
