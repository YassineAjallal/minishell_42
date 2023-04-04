/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:18:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/04 22:39:32 by yajallal         ###   ########.fr       */
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

	i = 0;
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
char *ft_cd(char *path)
{
	char **splitpath;
	char *current_path;
	char *new_path;
	int i;
	
	i = 0;
	current_path = ft_pwd();
	splitpath = ft_split(current_path, '/');

	if (path[0] == '/')
		new_path = path;
	else if (ft_strlen(path) == 1 && path[0] == '.')
		new_path = current_path;
	else if (ft_strlen(path) == 2 && path[0] == '.' && path[1] == '.')
		new_path = multiple_join(splitpath, ft_strlen2d(splitpath) - 1);
	else if (!ft_strchr(path, '/'))
	{
		path = ft_strjoin("/", path);
		new_path = ft_strjoin(current_path, path);
	}
	return (new_path);
}

int main()
{
	printf("%s\n", ft_cd("yassine"));
}