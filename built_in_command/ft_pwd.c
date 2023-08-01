/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:29:26 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/28 11:00:06 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

void	ft_pwd(t_command *cmd)
{
	char	buffer[PATH_MAX];

	getcwd(buffer, PATH_MAX);
	ft_putstr_fd(buffer, 1);
	ft_putchar_fd('\n', 1);
	cmd->g_info->exit_code = 0;
}
