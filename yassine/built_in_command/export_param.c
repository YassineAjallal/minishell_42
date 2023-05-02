/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:14:36 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/02 15:42:20 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"
int already_exist(char *name, t_env *env)
{
	int i;
	
	i = 0;
	while (i < env->nb_variables)
	{
		if (ft_strcmp(name, env->variables[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}
int valid_name(char *name)
{
	int i;

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

int ft_export(t_command *cmd, t_global_info *g_info)
{
	char **equal_split;
	int error_count;
	int equal_pos;
	t_variable new_var;
	int i;

	i = 1;
	error_count = 0;
	while (cmd->cmd_parameter[i])
	{
		equal_split = ft_split(cmd->cmd_parameter[i], '=');
		if (ft_strlen2d(equal_split) == 1)
		{
			if (valid_name(equal_split[0]))
			{
				new_var.name = ft_strdup(equal_split[0]);
				if (ft_strchr(cmd->cmd_parameter[i], '='))
					new_var.value = ft_strdup("");
				else
					new_var.value = NULL;
				fill_var_list(new_var, g_info->export_env);
			}
			else
				error_count++;
		}
		else if (ft_strlen2d(equal_split) > 1)
		{
			if (valid_name(equal_split[0]))
			{		
				equal_pos = get_until_equal(cmd->cmd_parameter[i]);
				new_var.name = ft_substr(cmd->cmd_parameter[i], 0, equal_pos);
				new_var.value = ft_substr(cmd->cmd_parameter[i], equal_pos + 1, ft_strlen(cmd->cmd_parameter[i]));
				export_normal_var(new_var, g_info);
			}
			else
				error_count++;
		}
		else
			error_count++;
		i++;
	}
	return (error_count);
}

