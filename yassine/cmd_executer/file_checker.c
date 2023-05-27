/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/17 19:56:53 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_executer.h"

int	ft_checkf(char *file)
{
	if (access(file, F_OK) < 0)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		return (0);
	}
	return (1);
}

int	ft_checkw(char *file)
{
	if (access(file, W_OK) < 0)
	{
		ft_perror(2, "minishell: %s: Permission denied\n", file);
		return (0);
	}
	return (1);
}

int	ft_checkr(char *file)
{
	if (access(file, R_OK) < 0)
	{
		ft_perror(2, "minishell: %s: Permission denied\n", file);
		return (0);
	}
	return (1);
}

int	ft_checkx(char *file)
{
	if (access(file, X_OK) < 0)
	{
		ft_perror(2, "minishell: %s: Permission denied\n", file);
		return (0);
	}
	return (1);
}
