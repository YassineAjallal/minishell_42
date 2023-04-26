/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/26 22:48:00 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

void	ft_perror(int fd, char *s, char *str)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == 's')
				ft_putstr_fd(str, fd);
		}
		else
			ft_putchar_fd(s[i], fd);
		if (s[i])
			i++;
	}
}

void	ft_checkf(char *file, int ex)
{
	if (access(file, F_OK) < 0)
	{
		ft_perror(2, "minishell: %s: No such file or directory", file);
		exit(ex);
	}
}

void	ft_checkw(char *file, int ex)
{
	if (access(file, W_OK) < 0)
	{
		ft_perror(2, "minishell: %s: permission denied\n", file);
		exit(ex);
	}
}

void	ft_checkr(char *file, int ex)
{
	if (access(file, R_OK) < 0)
	{
		ft_perror(2, "minishell: %s: permission denied\n", file);
		exit(ex);
	}
}

void	ft_checkx(char *file, int ex)
{
	if (access(file, X_OK) < 0)
	{
		ft_perror(2, "minishell: %s: permission denied\n", file);
		exit(ex);
	}
}
int main()
{
	ft_checkx("tools.h", 126);
}