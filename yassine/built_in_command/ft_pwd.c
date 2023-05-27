/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:29:26 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 13:12:16 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

void	ft_pwd(t_command *cmd)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd(buffer, 0);
	ft_putstr_fd(buffer, 1);
	ft_putchar_fd('\n', 1);
	free(buffer);
	cmd->g_info->exit_code = 0;
}
