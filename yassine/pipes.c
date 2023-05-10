/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:57:21 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/06 12:50:39 by yajallal         ###   ########.fr       */
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
	int     pids[nb_pipe + 1];
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
		else
			pids[i] = pid;
		if (cmds[i]->herdoc == true)
			wait(NULL);
	}
	close_pipes(pipe_arr, nb_pipe);
	i = -1;
	while (++i < nb_pipe + 1)
		waitpid(pids[i], &status, 0);
    printf("status %d\n", WEXITSTATUS(status));		
	return (0);
}

int main(int ac, char **av, char **env)
{
	if (ac > 1)
		return (0);
	if (av[1])
		return (0);
	char *input;
	char **split;
	t_global_info *g_info;
	t_command **cmd;
	int i;
	i = 0;
	
	g_info = malloc(sizeof(t_global_info));
	g_info->environ = dup_env(env);
	g_info->export_env = dup_env(env);
	g_info->env_array = convert_env_array(g_info->environ);
	g_info->nb_pipe = 2;
	while(1)
	{
		input = readline("\e[1;36m➜  \e[1;33mminishell \e[1;32m✗ \e[0;00m");
		add_history(input);
		split = lexer(input);
		cmd = rmplir_strct(split, g_info);
		pipes(cmd, g_info->nb_pipe);
	}
	
}

// ls | sleep 5 | echo y
// cat << yajallal | wc -l | ls
// readline("\e[1;36m➜  \e[1;33mminishell \e[1;32m✗ \e[0;00m");