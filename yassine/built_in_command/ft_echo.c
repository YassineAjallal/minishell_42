/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:30:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/02 12:58:12 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

// int get_next_space(char *echo_str, int current_pos)
// {
// 	int next_space;
// 	next_space = 0;

// 	while(echo_str[current_pos] != ' ' && echo_str[current_pos])
// 	{
// 		next_space++;
// 		current_pos++;
// 	}
// 	return (next_space);
// }

// int check_var_in_env(char *env_var, int var_length, char **env)
// {
// 	int i;
	
// 	i = 0;
// 	while(env[i])
// 	{
// 		if (ft_strncmp(env_var, env[i], var_length) == 0)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

void ft_echo(t_command *cmd)
{
	int i;
	i = 2;
	
	while (cmd->cmd_parameter[i])
	{
		printf ("%s", cmd->cmd_parameter[i]);
		i++;
		if (cmd->cmd_parameter[i])
			printf(" ");
	}
	if (ft_strcmp(cmd->cmd_parameter[1], "-n") != 0)
		printf("\n");
}

