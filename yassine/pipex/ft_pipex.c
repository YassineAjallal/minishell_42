/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:57:37 by yajallal          #+#    #+#             */
/*   Updated: 2023/01/13 11:48:53 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	main(int ac, char **av, char **envp)
{
	int	fd_pipe[2];

	if (ac != 5)
		ft_errors("we need 5 arguments", 1);
	if (pipe(fd_pipe) < 0)
		ft_errors("pipex : pipe: piping error", 1);
	ft_fork(fd_pipe, av, envp);
}
