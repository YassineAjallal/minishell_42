/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:26:04 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/01 23:26:10 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void ft_malloc_pipes(int **pipes, int nb_pipe)
{
	int i;
	i = 0;
	pipes = malloc(sizeof(int *) * nb_pipe);
	while (i < nb_pipe)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
}

int piping(int infile, int outfile, int nb_pipe, char **cmds, char **envp)
{

	pid_t pid;
	int pipes[nb_pipe][2];
	char **strings;
	char **string;
	int i;
	int j;
	i = 0;
	while (i < nb_pipe)
	{
		pipe(pipes[i]);
		i++;
	}
	i = 0;
	strings = ft_split("ls -la|grep yajallal|grep 3|grep pipex|grep 11", '|');
	pid = fork();
	if (pid == 0)
	{
		string = ft_split(strings[i], ' ');
		dup2(pipes[0][1], STDOUT_FILENO);
		j = 0;
			while (j < 4)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
		execve("/bin/ls", string, envp);
	}
	i++;
	while (i < 4)
	{
		pid = fork();
		if (pid == 0)
		{
			string = ft_split(strings[i], ' ');
			dup2(pipes[i - 1][0], STDIN_FILENO);
			dup2(pipes[i][1], STDOUT_FILENO);
			j = 0;
			while (j < 4)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
			execve("/usr/bin/grep", string, envp);
		}
		i++;
	}
	pid = fork();
	if (pid == 0)
	{
		string = ft_split(strings[i], ' ');
		dup2(pipes[i - 1][0], STDIN_FILENO);
		j = 0;
			while (j < 4)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}
		execve("/usr/bin/grep", string, envp);
	}
	i = 0;
	while (i < 4)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		wait(NULL);
		i++;
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	piping(1, 1, 4, NULL, env);
}
