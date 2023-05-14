/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:18:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/13 21:23:37 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int ft_cd(t_command *cmd)
{
	char *new_path;
	char **home;
	int home_pos;
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
			ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
			return (0);
		}
	}
	else
	{
		if (search_env(cmd->g_info->environ, "HOME", &home_pos))
		{	
			if (chdir(cmd->g_info->environ->variables[home_pos].value) != 0)
			{
				ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
				return (0);
			}
		}
		else
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (0);
		}
	}
	return (1);
}
