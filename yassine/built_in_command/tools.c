/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 00:28:19 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/27 22:10:48 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int ft_strlen2d(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char *multiple_join(char **path, int length)
{
	int i;
	char *tmp;
	char *new_path = NULL;
	char *add_slash;

	i = 1;
	tmp = ft_strjoin(new_path, path[0]);
	free(new_path);
	new_path = tmp;
	while (i < length)
	{
		add_slash = ft_strjoin("/", path[i]);
		tmp = ft_strjoin(new_path, add_slash);
		free(new_path);
		new_path = tmp;
		i++;
	}
	return (new_path);
}

void	ft_free2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}