/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:18:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/26 22:28:24 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int ft_cd(char *path)
{
	char *new_path;
	char **home;
	int i;
	
	i = 0;
	if (path[0] == '~')
	{
		home = ft_split(path, '/');
		free(home[0]);
		home[0] = getenv("HOME");
		new_path = multiple_join(home, ft_strlen2d(home));
		free(path);
		path = new_path;
	}
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n",path);
		return (0);
	}
	return (1);
}
