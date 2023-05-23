/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 11:41:49 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/23 18:26:47 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

void	ft_perror(int fd, char *s, char *str)
{
	int	i;

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

int	exit_one_pram(t_command *cmd)
{
	int	i;
	int	exit;

	i = 0;
	if (cmd->cmd_parameter[1][i] == '-')
		i++;
	while (cmd->cmd_parameter[1][i])
	{
		if (!ft_isdigit(cmd->cmd_parameter[1][i]))
		{
			ft_perror(2, "minishell: exit: %s: numeric argument required\n", \
			cmd->cmd_parameter[1]);
			cmd->g_info->exit_code = 255;
			return (0);
		}
		i++;
	}
	exit = ft_atoi(cmd->cmd_parameter[1]);
	if (exit > 256 || exit < 0)
		cmd->g_info->exit_code = exit % 256;
	else
		cmd->g_info->exit_code = exit;
	return (1);
}

int	exit_more_param(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd_parameter[1][i] == '-')
			i++;
	while (cmd->cmd_parameter[1][i])
	{
		if (!ft_isdigit(cmd->cmd_parameter[1][i]))
		{
			ft_perror(2, "minishell: exit: %s: numeric argument required\n", \
			cmd->cmd_parameter[1]);
			cmd->g_info->exit_code = 255;
			return (0);
		}
		i++;
	}
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	cmd->g_info->exit_code = 1;
	return (0);
}

int	ft_exit(t_command *cmd)
{
	if (ft_strlen2d(cmd->cmd_parameter) == 2)
	{
		if (!exit_one_pram(cmd))
			return (0);
	}
	else if (ft_strlen2d(cmd->cmd_parameter) > 2)
	{
		if (!exit_more_param(cmd))
			return (0);
	}
	return (1);
}
