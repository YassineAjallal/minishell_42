/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 00:28:19 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/23 18:55:02 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int	ft_strlen2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*multiple_join(char **path, int length)
{
	int		i;
	char	*tmp;
	char	*new_path;
	char	*add_slash;

	i = 1;
	new_path = ft_strdup("");
	new_path = ft_strjoin(new_path, path[0]);
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
