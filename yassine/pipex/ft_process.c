/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:48:19 by yajallal          #+#    #+#             */
/*   Updated: 2023/01/13 12:13:35 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_fork(int *fd_pipe, char **av, char **envp)
{
	int	pid;
	int	input;
	int	output;

	pid = fork();
	if (pid < 0)
		ft_errors("pipex: fork: forking error", 1);
	if (pid == 0)
	{
		input = open(av[1], O_RDONLY);
		if (input < 0)
			ft_errors("pipex: input: No such file or directory", 1);
		ft_child(input, fd_pipe, av, envp);
	}
	output = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (output < 0)
		ft_errors("pipex : open: opening error", 1);
	ft_parent(output, fd_pipe, av, envp);
}

void	ft_redirect(int f1, int f2, int f3)
{
	dup2(f1, STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	close(f1);
	close(f2);
	close(f3);
}
