/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:13:03 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/30 11:32:22 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_executer.h"

int	stdin_redirect(t_command *cmd)
{
	int	i;

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
			if (!redirect_in(cmd->infile[i], cmd->g_info))
			{
				cmd->g_info->exit_code = 1;
				return (0);
			}
			i++;
		}
	}
	return (1);
}

int	stdout_redirect(t_command *cmd)
{
	int	stdout_fd;
	int	i;

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

void	search_built_in(t_command *cmd)
{
	char	**all_built_in;
	int		i;

	i = 0;
	if (!cmd->cmd)
	{
		cmd->built_in = false;
		cmd->g_info->exit_code = 0;
	}
	all_built_in = NULL;
	if (cmd->cmd)
	{
		all_built_in = ft_split("echo cd pwd export unset env exit", ' ');
		while (all_built_in[i])
		{
			if (!ft_strcmp(cmd->cmd, all_built_in[i]))
			{
				cmd->built_in = true;
				return ;
			}
			else
				cmd->built_in = false;
			i++;
		}
	}
}

void	exec_non_built_in(t_command *cmd, t_global_info *g_info)
{
	int	exit_code;

	if (!stdin_redirect(cmd) || !stdout_redirect(cmd))
	{
		ft_malloc(0, 0);
		exit_code = g_info->exit_code;
		free_infos(g_info);
		exit(exit_code);
	}
	if (cmd_validation(cmd))
	{
		execve(cmd->command_path, cmd->cmd_parameter, \
		cmd->g_info->env_array);
	}
	else
	{
		ft_malloc(0, 0);
		exit_code = g_info->exit_code;
		free_infos(g_info);
		exit(exit_code);
	}
}

void	cmd_exec(t_command *cmd, t_global_info *g_info)
{
	search_built_in(cmd);
	if (cmd->built_in == false)
		exec_non_built_in(cmd, g_info);
	else
	{
		if (!exec_built_in(cmd, g_info))
		{
			ft_malloc(0, 0);
			free_infos(g_info);
			exit(EXIT_FAILURE);
		}
		else
		{
			ft_malloc(0, 0);
			free_infos(g_info);
			exit(EXIT_SUCCESS);
		}
	}
}
