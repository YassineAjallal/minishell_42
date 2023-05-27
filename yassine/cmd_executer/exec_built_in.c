/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 19:43:17 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 19:46:41 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_executer.h"

int	exec_built_in_p1(t_command *cmd)
{
	if (!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(cmd);
	else if (!ft_strcmp(cmd->cmd, "cd"))
	{
		if (!ft_cd(cmd))
			return (0);
	}
	else if (!ft_strcmp(cmd->cmd, "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		ft_unset(cmd);
	return (1);
}

void	exec_built_in_p2(t_command *cmd, t_global_info *g_info)
{
	if (!ft_strcmp(cmd->cmd, "export"))
	{
		if (ft_strlen2d(cmd->cmd_parameter) == 1)
			export_no_param(cmd);
		else
			ft_export(cmd);
	}
	else if (!ft_strcmp(cmd->cmd, "exit"))
	{
		if (ft_exit(cmd))
		{
			ft_malloc(0, 0);
			exit (g_info->exit_code);
		}
	}
}

int	exec_built_in(t_command *cmd, t_global_info *g_info)
{
	if (!stdin_redirect(cmd) || !stdout_redirect(cmd))
		return (0);
	if (!exec_built_in_p1(cmd))
		return (0);
	exec_built_in_p2(cmd, g_info);
	return (1);
}
