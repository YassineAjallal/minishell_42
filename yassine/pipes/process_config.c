/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:25:35 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 12:23:13 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	child_config(t_command *cmd, int dup_stdin, \
int dup_stdout, int (*pipes)[2])
{
	if (cmd->herdoc == false)
	{
		dup2(dup_stdin, STDIN_FILENO);
		dup2(dup_stdout, STDOUT_FILENO);
		close_pipes(pipes, cmd->g_info->nb_pipe);
	}
	else
			cmd->herdoc_stdout = dup_stdout;
	cmd_exec(cmd, cmd->g_info);
}

void	parent_config(t_command *cmd, int pid)
{
	if (cmd->herdoc == true)
	{
		waitpid(pid, &cmd->g_info->status, 0);
		cmd->g_info->exit_code = WEXITSTATUS(cmd->g_info->status);
	}
}

void	wait_config(t_global_info *g_info, int pids[])
{
	int	i;

	i = -1;
	while (++i < g_info->nb_pipe + 1)
		waitpid(pids[i], &g_info->status, 0);
	g_info->exit_code = WEXITSTATUS(g_info->status);
}

int	fork_config(t_command *cmd, int dup_stdin, \
int dup_stdout, int (*pipe_arr)[2])
{
	int	pid;
	char **tmp;

	tmp = expand_all_param(cmd);
	cmd->cmd_parameter = tmp;
	pid = fork();
	if (pid == 0)
		child_config(cmd, dup_stdin, dup_stdout, pipe_arr);
	else if (pid > 0)
		parent_config(cmd, pid);
	else
	{
		ft_putstr_fd("minishell: fork error\n", 2);
		return (0);
	}
	return (pid);
}
