/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:18:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/28 18:38:02 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int	cd_no_param(t_command *cmd)
{
	int	home_pos;

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
	return (1);
}

int	cd_with_param(t_command *cmd)
{
	char	**home;

	if (cmd->cmd_parameter[1][0] == '~')
	{
		home = ft_split(cmd->cmd_parameter[1], '/');
		home[0] = getenv("HOME");
		cmd->cmd_parameter[1] = multiple_join(home, ft_strlen2d(home));
	}
	if (chdir(cmd->cmd_parameter[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		cmd->g_info->exit_code = 1;
		return (0);
	}
	return (1);
}

int	ft_cd(t_command *cmd)
{
	char		buffer[PATH_MAX];
	t_variable	pwd_var;

	getcwd(buffer, PATH_MAX);
	pwd_var.name = env_strdup("OLDPWD");
	pwd_var.value = env_strdup(buffer);
	export_normal_var(pwd_var, cmd->g_info);
	free(pwd_var.name);
	free(pwd_var.value);
	if (ft_strlen2d(cmd->cmd_parameter) >= 2)
		if (!cd_with_param(cmd))
			return (0);
	if (ft_strlen2d(cmd->cmd_parameter) == 1)
		if (!cd_no_param(cmd))
			return (0);
	getcwd(buffer, PATH_MAX);
	pwd_var.name = env_strdup("PWD");
	pwd_var.value = env_strdup(buffer);
	export_normal_var(pwd_var, cmd->g_info);
	free(pwd_var.name);
	free(pwd_var.value);
	cmd->g_info->exit_code = 0;
	return (1);
}
