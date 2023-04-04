/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:29:26 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/04 22:02:01 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

char *ft_pwd(void)
{
	char *path;
	char *buffer;

	buffer = NULL;
	path = getcwd(buffer, 0);
	if (!path)
		return (NULL);
	return (path);	
}