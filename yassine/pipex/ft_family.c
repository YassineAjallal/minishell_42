/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_family.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:47:18 by yajallal          #+#    #+#             */
/*   Updated: 2023/01/13 12:11:59 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_child(int input, int *fd_pipe, char **av, char **envp)
{
	char	**cmd;
	char	*fpath;

	ft_checkf(av[1], "pipex: no such file or directory:", 1);
	ft_checkr(av[1], 1);
	ft_redirect(input, fd_pipe[1], fd_pipe[0]);
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

void	ft_parent(int output, int *fd_pipe, char **av, char **envp)
{
	char	**cmd;
	char	*fpath;

	ft_checkw(av[4], 1);
	ft_redirect(fd_pipe[0], output, fd_pipe[1]);
	cmd = ft_quotes(av[3]);
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
