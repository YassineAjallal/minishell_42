/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:13:03 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/23 12:21:21 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_executer.h"

int stdin_redirect(t_command *cmd)
{
	int i;

	i = 0;
	if (cmd->redirect_in == true)
	{
		if (!redirect_herdoc(cmd))
		{
			cmd->g_info->exit_code = 1;
			return (0);
		}
		while (cmd->infile[i])
		{
			if(!redirect_in(cmd->infile[i], cmd->g_info))
			{
				cmd->g_info->exit_code = 1;
				return (0);
			}
			i++;
		}
	}
	return (1);
}

int stdout_redirect(t_command *cmd)
{
	int stdout_fd;
	int i;

	stdout_fd = -1;
	if (cmd->redirect_out == true)
	{
		i = 0;
		while (cmd->outfile[i])
		{
			if (!redirect_out(cmd->outfile[i], &stdout_fd, cmd->g_info))
			{
				cmd->g_info->exit_code = 1;
				return (0);
			}
			i++;
		}
		if (dup2(stdout_fd, STDOUT_FILENO) < 0)
		{
			ft_putstr_fd("minishell: redirect error\n", 2);
			cmd->g_info->exit_code = 1;
			return (0);
		}
	}
	return (1);
}

void search_built_in(t_command *cmd)
{
	char **all_built_in;
	int i;

	i = 0;
	if (!cmd->cmd)
	{
		cmd->built_in = false;
		cmd->g_info->exit_code = 0;
	}
	if (cmd->cmd)
	{
		all_built_in = ft_split("echo cd pwd export unset env exit", ' ');
		while (all_built_in[i])
		{
			if (!ft_strcmp(cmd->cmd, all_built_in[i]))
			{
				cmd->built_in = true;
				return;
			}
			else
				cmd->built_in = false;
			i++;
		}
	}
}
int exec_built_in(t_command *cmd)
{
	if(!stdin_redirect(cmd))
		return (0);
	if(!stdout_redirect(cmd))
		return (0);
	if(!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(cmd);
	else if (!ft_strcmp(cmd->cmd, "cd"))
	{
		if (!ft_cd(cmd))
			return (0);
	}
	else if (!ft_strcmp(cmd->cmd , "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->cmd , "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(cmd->cmd , "export"))
	{
		if (ft_strlen2d(cmd->cmd_parameter) == 1)
			export_no_param(cmd);
		else
			ft_export(cmd);
	}
	else if (!ft_strcmp(cmd->cmd, "exit"))
	{
		if (ft_exit(cmd))
			exit (cmd->g_info->exit_code);
	}
	return (1);
}

void cmd_exec(t_command *cmd)
{
	search_built_in(cmd);
	if (cmd->built_in == false)
	{
		if(!stdin_redirect(cmd))
			exit(cmd->g_info->exit_code);
		if(!stdout_redirect(cmd))
			exit(cmd->g_info->exit_code);
		if(cmd_validation(cmd))
			execve(cmd->command_path, cmd->cmd_parameter, cmd->g_info->env_array);
		else
			exit(cmd->g_info->exit_code);
	}
	else
	{
		if (!exec_built_in(cmd))
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
}
