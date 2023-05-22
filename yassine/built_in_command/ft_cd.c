/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:18:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/22 12:47:39 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int ft_cd(t_command *cmd)
{
	char *new_path;
	char **home;
	char *buffer;
	int home_pos;
	t_variable pwd_var;
	int i;
	
	i = 0;

	buffer = NULL;
	pwd_var.name = ft_strdup("OLDPWD");
	pwd_var.value = getcwd(buffer, 0);
	export_normal_var(pwd_var, cmd->g_info);
	if (ft_strlen2d(cmd->cmd_parameter) >= 2)
	{		
		if (cmd->cmd_parameter[1][0] == '~')
		{
			home = ft_split(cmd->cmd_parameter[1], '/');
			free(home[0]);
			home[0] = getenv("HOME");
			new_path = multiple_join(home, ft_strlen2d(home));
			free(cmd->cmd_parameter[1]);
			cmd->cmd_parameter[1] = new_path;
		}
		if (chdir(cmd->cmd_parameter[1]) != 0)
		{
			ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
			cmd->g_info->exit_code = 1;
			return (0);
		}
	}
	else
	{
		if (search_env(cmd->g_info->environ, "HOME", &home_pos))
		{	
			if (chdir(cmd->g_info->environ->variables[home_pos].value) != 0)
			{
				ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
				cmd->g_info->exit_code = 1;
				return (0);
			}
		}
		else
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			cmd->g_info->exit_code = 1;
			return (0);
		}
	}
	pwd_var.name = ft_strdup("PWD");
	pwd_var.value = getcwd(buffer, 0);
	export_normal_var(pwd_var, cmd->g_info);
	cmd->g_info->exit_code = 0;
	return (1);
}
