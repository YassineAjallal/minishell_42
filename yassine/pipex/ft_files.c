/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:39:58 by yajallal          #+#    #+#             */
/*   Updated: 2023/01/13 12:12:05 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

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
