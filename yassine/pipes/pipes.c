/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:57:21 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 19:19:26 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	one_built_in(t_command *cmd, t_global_info *g_info)
{
	char	**tmp;

	g_info->old_stdout = dup(STDOUT_FILENO);
	g_info->old_stdin = dup(STDIN_FILENO);
	tmp = expand_all_param(cmd);
	cmd->cmd_parameter = tmp;
	exec_built_in(cmd, g_info);
	dup2(g_info->old_stdout, STDOUT_FILENO);
	dup2(g_info->old_stdin, STDIN_FILENO);
	ft_malloc(0, 0);
}

int	*cmds_run(int (*pipe_arr)[2], t_command **cmds, \
t_global_info *g_info, int *pids)
{
	int	i;
	int	dup_stdin;
	int	dup_stdout;
	int	pid;

	i = -1;
	dup_stdin = 0;
	dup_stdout = pipe_arr[i][1];
	while (++i < g_info->nb_pipe + 1)
	{
		if (i != 0)
			dup_stdin = pipe_arr[i - 1][0];
		if (i == g_info->nb_pipe)
			dup_stdout = 1;
		else
			dup_stdout = pipe_arr[i][1];
		pid = fork_config(cmds[i], dup_stdin, dup_stdout, pipe_arr);
		if (pid > 0)
			pids[i] = pid;
	}
	return (pids);
}

int	pipes(t_command **cmds, t_global_info *g_info)
{
	int		(*pipe_arr)[2];
	int		*pids;

	search_built_in(cmds[0]);
	if (cmds[0]->built_in == true && g_info->nb_pipe == 0)
		one_built_in(cmds[0], g_info);
	else
	{	
		pipe_arr = ft_malloc(sizeof(int *) * g_info->nb_pipe, 1);
		if (!pipe_arr)
			return (0);
		pids = ft_malloc(sizeof(int) * (g_info->nb_pipe + 1), 1);
		if (!pids)
			return (0);
		if (!init_pipe(g_info->nb_pipe, pipe_arr))
			return (0);
		pids = cmds_run(pipe_arr, cmds, g_info, pids);
		close_pipes(pipe_arr, g_info->nb_pipe);
		wait_config(g_info, pids);
	}
	return (1);
}
