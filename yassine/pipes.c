/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:57:21 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/24 19:58:46 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_pipe(int pipes[][2], int nb_pipe)
{
	int i;
	
	i = 0;
	while (i < nb_pipe)
	{
		if (pipe(pipes[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

void close_pipes(int pipes[1][2], int nb_pipe)
{
	int i;
	
	i = 0;
	while (i < nb_pipe)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void child_config(t_command *cmd, int dup_stdin, int dup_stdout, int pipes[][2])
{
	if (cmd->herdoc == false)
	{
		dup2(dup_stdin, STDIN_FILENO);
		dup2(dup_stdout, STDOUT_FILENO);
		close_pipes(pipes, cmd->g_info->nb_pipe);
	}
	else
			cmd->herdoc_stdout = dup_stdout;
	cmd_exec(cmd);
}

void parent_config(t_command *cmd, int *status, int pid)
{
	if (cmd->herdoc == true)
	{
		waitpid(pid, status, 0);
		cmd->g_info->exit_code = WEXITSTATUS(status);
	}
}

int pipes(t_command **cmds, t_global_info *g_info)
{
	pid_t	pid;
	int		pipe_arr[g_info->nb_pipe][2];
	int     pids[g_info->nb_pipe + 1];
	int		i;
	int		dup_stdin;
	int		dup_stdout;
	int 	status;
	int 	status1;
	int j;

	i = -1;
	search_built_in(cmds[0]);
	if (cmds[0]->built_in == true && g_info->nb_pipe == 0)
	{
		g_info->old_stdout = dup(STDOUT_FILENO);
		g_info->old_stdin = dup(STDIN_FILENO);
		cmds[0]->cmd_parameter = expand_all_param(cmds[0]);
		exec_built_in(cmds[0]);
		dup2(g_info->old_stdout, STDOUT_FILENO);
		dup2(g_info->old_stdin, STDIN_FILENO);
	}
	else
	{	
		if (!init_pipe(pipe_arr, g_info->nb_pipe))
			return (0);
		dup_stdin = 0;
		dup_stdout = pipe_arr[i][1];
		while(++i < g_info->nb_pipe + 1)
		{
			cmds[i]->cmd_parameter = expand_all_param(cmds[i]);
			if (i != 0)
				dup_stdin = pipe_arr[i - 1][0];
			if (i == g_info->nb_pipe)
				dup_stdout = 1;
			else
				dup_stdout = pipe_arr[i][1];
			pid = fork();
			if (pid == 0)
				child_config(cmds[i], dup_stdin, dup_stdout, pipe_arr);
			else if (pid > 0)
			{
				pids[i] = pid;
				parent_config(cmds[i], &status, pid);
			}
			else
			{
				ft_putstr_fd("minishell: fork error\n", 2);
				return (0);
			}
		}
		close_pipes(pipe_arr, g_info->nb_pipe);
		i = -1;
		while (++i < g_info->nb_pipe + 1)
			waitpid(pids[i], &status, 0);
		g_info->exit_code = WEXITSTATUS(status);
	}
	return (1);
}
