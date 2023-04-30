/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:57:21 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/30 15:27:51 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_pipe(int **pipes, int nb_pipe)
{
	int i;
	
	i = 0;
	pipes = malloc(sizeof(int *) * nb_pipe);
	while (i < nb_pipe)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	while (i < nb_pipe)
	{
		if (pipe(pipes[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

void close_pipes(int **pipes, int nb_pipe)
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

int pipes(t_command **cmds, t_global_info *g_info)
{
	pid_t	pid;
	int		**pipe_arr;
	int		i;

	i = 0;
	if (!init_pipe(pipe_arr, g_info->nb_pipe))
		return (0);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe_arr[i][1], STDOUT_FILENO);
		close_pipes(pipe_arr, g_info->nb_pipe);
		cmd_exec(cmds[i]);
	}
	i++;
	// while(i < g_info->nb_pipe)
	// {
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{
	// 		dup2(pipe_arr[i - 1][0], STDIN_FILENO);
	// 		dup2(pipe_arr[i][1], STDOUT_FILENO);
	// 		close_pipes(pipe_arr, g_info->nb_pipe);
	// 		cmd_exec(cmds[i]);
	// 	}
	// 	i++;
	// }
	pid = fork();
	if (pid == 0)
	{
		printf("%d\n", i);
		// dup2(pipe_arr[i - 1][0], STDIN_FILENO);
		// close_pipes(pipe_arr, g_info->nb_pipe);
		cmd_exec(cmds[i]);
	}
	i = 0;
	while (i < g_info->nb_pipe + 1)
	{
		wait(NULL);
		i++;
	}
	return (0);
}
int main(int ac, char **av, char **env)
{
	t_global_info *g_info;
	t_command **cmd;
	int i;
	i = 0;
	cmd = malloc(sizeof(t_command *) * 2);
	while (i < 2)
	{
		cmd[i] = malloc(sizeof(t_command));
		i++;
	}
	
	g_info = malloc(sizeof(t_global_info));
	
	g_info->environ = dup_env(env);
	g_info->export_env = dup_env(env);
	g_info->env_array = convert_env_array(g_info->environ);
	g_info->nb_pipe = 1;

	cmd[0]->g_info = g_info;
	cmd[0]->cmd = ft_strdup("ls");
	cmd[0]->command_path = cmd_path(cmd[0]->cmd, cmd[0]->g_info->env_array);
	cmd[0]->cmd_parameter = ft_split("ls -l", ' ');
	/* redirect */
	cmd[0]->built_in = false;
	cmd[0]->redirect_in = false;
	cmd[0]->redirect_append = false;
	cmd[0]->redirect_out = false;
	cmd[0]->herdoc = false;

	cmd[1]->g_info = g_info;
	cmd[1]->cmd = ft_strdup("ls");
	cmd[1]->command_path = cmd_path(cmd[1]->cmd, cmd[1]->g_info->env_array);
	cmd[1]->cmd_parameter = ft_split("ls -l", ' ');
	/* redirect */
	cmd[1]->built_in = false;
	cmd[1]->redirect_in = false;
	cmd[1]->redirect_append = false;
	cmd[1]->redirect_out = false;
	cmd[1]->herdoc = false;

	// cmd[2]->g_info = g_info;
	// cmd[2]->cmd = ft_strdup("wc");
	// cmd[2]->command_path = cmd_path(cmd[2]->cmd, cmd[2]->g_info->env_array);
	// cmd[2]->cmd_parameter = ft_split("wc -l", ' ');
	// /* redirect */
	// cmd[2]->built_in = false;
	// cmd[2]->redirect_in = false;
	// cmd[2]->redirect_append = false;
	// cmd[2]->redirect_out = false;
	// cmd[2]->herdoc = false;

	pipes(cmd, g_info);
}
