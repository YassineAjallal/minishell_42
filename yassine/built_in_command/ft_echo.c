/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:30:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/14 21:07:35 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int just_n(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while(str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
void ft_echo(t_command *cmd)
{
	int i;
	int nl_print;

	i = 1;
	nl_print = 0;
	
	if (ft_strlen2d(cmd->cmd_parameter) == 1)
		printf("\n");
	else
	{
		while(just_n(cmd->cmd_parameter[i]))
		{
			nl_print = 1;
			i++;
		}
		while (cmd->cmd_parameter[i])
		{
			ft_putstr_fd(cmd->cmd_parameter[i], 1);
			i++;
			if (cmd->cmd_parameter[i])
				ft_putchar_fd(' ', 1);
		}
		if (nl_print == 0)
			ft_putchar_fd('\n', 1);
	}
}

