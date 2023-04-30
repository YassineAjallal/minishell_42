/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:26:04 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/30 14:24:59 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int int_pipe(int **pipes, int nb_pipe)
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

int close_pipes(int **pipes, int nb_pipe)
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

// int exec_cmd(int stdin, int stdout, char *cmd, int pipes, int nb_pipe)
// {
// 	if (stdin != 0)
// 		dup2(stdin, STDIN_FILENO);
// 	if (stdout != 1)
// 		dup2(stdout, STDOUT_FILENO);
// 	close_pipes(pipes, nb_pipe);
	
	
// }

// int piping(t_command **cmds)
// {

// 	pid_t pid;
// 	int pipes[nb_pipe][2];
// 	int i;
// 	int j;

// 	i = 0;
// 	if (!init_pipe(pipes, nb_pipe))
// 		return (0);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(pipes[0][1], STDOUT_FILENO);
// 		cmd_exec()
// 	}
// 	i++;
// 	while (i < nb_pipe + 1)
// 	{
// 		if (i = 0)
// 		{
			
// 		}
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			dup2(pipes[i - 1][0], STDIN_FILENO);
// 			dup2(pipes[i][1], STDOUT_FILENO);
// 			execve("/usr/bin/grep", string, envp);
// 		}
// 		i++;
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(pipes[i - 1][0], STDIN_FILENO);
// 		execve("/usr/bin/grep", string, envp);
// 	}

// 	i = 0;
// 	while (i < 5)
// 	{
// 		wait(NULL);
// 		i++;
// 	}
// 	return (0);
// }
