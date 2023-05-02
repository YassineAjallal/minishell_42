/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:18:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/01 20:00:28 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int ft_cd(t_command *cmd)
{
	char *new_path;
	char **home;
	int i;
	
	i = 0;
	if (ft_strlen2d(cmd->cmd_parameter) >= 2)
	{		
		if (cmd->cmd_parameter[1][0] == '~')
		{
			home = ft_split(cmd->cmd_parameter[1], '/');
			free(home[0]);
			home[0] = getenv("HOME");
			new_path = multiple_join(home, ft_strlen2d(home));
			free(cmd->cmd_parameter[1]);
			cmd->cmd_parameter[1] = new_path;
		}
		if (chdir(cmd->cmd_parameter[1]) != 0)
		{
			printf("minishell: cd: %s: No such file or directory\n", cmd->cmd_parameter[1]);
			return (0);
		}
	}
	else
	{
		if (chdir(getenv("HOME")) != 0)
		{
			printf("minishell: cd: %s: No such file or directory\n", getenv("HOME"));
			return (0);
		}
	}
	return (1);
}
