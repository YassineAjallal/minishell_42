/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:57:21 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/03 18:33:21 by yajallal         ###   ########.fr       */
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

int pipes(t_command **cmds, int nb_pipe)
{
	pid_t	pid;
	int		pipe_arr[nb_pipe][2];
	int		i;
	int		dup_stdin;
	int		dup_stdout;
	int 	status;

	i = -1;
	if (!init_pipe(pipe_arr, nb_pipe))
		return (0);
	dup_stdin = 0;
	dup_stdout = pipe_arr[i][1];
	while(++i < nb_pipe + 1)
	{
		if (i != 0)
			dup_stdin = pipe_arr[i - 1][0];
		if (i == nb_pipe)
			dup_stdout = 1;
		else
			dup_stdout = pipe_arr[i][1];
		pid = fork();
		if (pid == 0)
		{
			dup2(dup_stdin, STDIN_FILENO);
			if (cmds[i]->herdoc == false)
			{
				dup2(dup_stdout, STDOUT_FILENO);
				close_pipes(pipe_arr, nb_pipe);
			}
			else
				cmds[i]->herdoc_stdout = dup_stdout;
			cmd_exec(cmds[i]);
		}
		if (cmds[i]->herdoc == true)
			wait(NULL);
	}
	close_pipes(pipe_arr, nb_pipe);
	i = -1;
	while (++i < nb_pipe + 1)
		wait(&status);
    // printf("status %d\n", WEXITSTATUS(status));		
	return (0);
}

int main(int ac, char **av, char **env)
{
	t_global_info *g_info;
	t_command **cmd;
	int i;
	i = 0;
	cmd = malloc(sizeof(t_command *) * 3);
	while (i < 3)
	{
		cmd[i] = malloc(sizeof(t_command));
		i++;
	}
	
	g_info = malloc(sizeof(t_global_info));
	
	g_info->environ = dup_env(env);
	g_info->export_env = dup_env(env);
	g_info->env_array = convert_env_array(g_info->environ);
	g_info->nb_pipe = 2;

	cmd[0]->g_info = g_info;
	cmd[0]->cmd = ft_strdup("cat");
	cmd[0]->command_path = cmd_path(cmd[0]->cmd, cmd[0]->g_info->env_array);
	cmd[0]->cmd_parameter = ft_split("cat", ' ');
	/* redirect */
	cmd[0]->built_in = false;
	cmd[0]->redirect_in = false;
	cmd[0]->redirect_append = false;
	cmd[0]->redirect_out = false;
	cmd[0]->herdoc = true;
	cmd[0]->delemiter = ft_strdup("yajallal");

	// cmd[1]->g_info = g_info;
	// cmd[1]->cmd = ft_strdup("wc");
	// cmd[1]->command_path = cmd_path(cmd[1]->cmd, cmd[1]->g_info->env_array);
	// cmd[1]->cmd_parameter = ft_split("wc -l", ' ');
	// /* redirect */
	// cmd[1]->built_in = false;
	// cmd[1]->redirect_in = false;
	// cmd[1]->redirect_append = false;
	// cmd[1]->redirect_out = false;
	// cmd[1]->herdoc = false;

	// cmd[2]->g_info = g_info;
	// cmd[2]->cmd = ft_strdup("ls");
	// cmd[2]->command_path = cmd_path(cmd[2]->cmd, cmd[2]->g_info->env_array);
	// cmd[2]->cmd_parameter = ft_split("ls", ' ');
	// /* redirect */
	// cmd[2]->built_in = false;
	// cmd[2]->redirect_in = false;
	// cmd[2]->redirect_append = false;
	// cmd[2]->redirect_out = false;
	// cmd[2]->herdoc = false;
	cmd_exec(cmd[1]);

	// cmd[3]->g_info = g_info;
	// cmd[3]->cmd = ft_strdup("wc");
	// cmd[3]->command_path = cmd_path(cmd[3]->cmd, cmd[3]->g_info->env_array);
	// cmd[3]->cmd_parameter = ft_split("wc -l", ' ');
	// /* redirect */
	// cmd[3]->built_in = false;
	// cmd[3]->redirect_in = false;
	// cmd[3]->redirect_append = false;
	// cmd[3]->redirect_out = false;
	// cmd[3]->herdoc = false;

	// pipes(cmd, g_info->nb_pipe);
	// while(1)
	// {
		
	// 	readline("\e[1;36m➜  \e[1;33mminishell \e[1;32m✗ \e[0;00m");
	// }
}

// ls | sleep 5 | echo y
// cat << yajallal | wc -l | ls
// readline("\e[1;36m➜  \e[1;33mminishell \e[1;32m✗ \e[0;00m");