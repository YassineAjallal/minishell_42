/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:12:04 by yajallal          #+#    #+#             */
/*   Updated: 2023/03/30 23:55:29 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_checkf(char *file, char *msg, int ex)
{
	if (access(file, F_OK) < 0)
	{
		ft_perror(2, "%s %s", msg, file);
		exit(ex);
	}
}

void	ft_checkw(char *file, int ex)
{
	if (access(file, W_OK) < 0)
	{
		ft_perror(2, "pipex: %s: permission denied\n", file);
		exit(ex);
	}
}

void	ft_checkr(char *file, int ex)
{
	if (access(file, R_OK) < 0)
	{
		ft_perror(2, "pipex: %s: permission denied\n", file);
		exit(ex);
	}
}

void	ft_checkx(char *cmd, int ex)
{
	if (access(cmd, X_OK) < 0)
	{
		ft_perror(2, "pipex: %s: permission denied\n", cmd);
		exit(ex);
	}
}
void	ft_redirect(int f1, int f2, int f3)
{
	dup2(f1, STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	close(f1);
	close(f2);
	close(f3);
}

void	ft_child(int pipeinput, int pipeoutput, char **av, char **envp)
{
	char	**cmd;
	char	*fpath;

	ft_checkf(av[1], "pipex: no such file or directory:", 1);
	ft_checkr(av[1], 1);
	dup2(pipeinput, STDIN_FILENO);
	dupe2(pipeoutput, STDOUT_FILENO);
	cmd = ft_quotes(av[2]);
	fpath = ft_cmdpath(cmd[0], envp);
	if (!fpath)
	{
		ft_perror(2, "pipex: %s: command not found\n", cmd[0]);
		free(fpath);
		exit(127);
	}
	ft_checkx(fpath, 126);
	execve(fpath, cmd, envp);
}