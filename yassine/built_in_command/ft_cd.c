/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:18:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/18 18:00:42 by yajallal         ###   ########.fr       */
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

int main()
{
	char **line = ft_split(ft_pwd(), '/');
	char *prompt = ft_strjoin(line[ft_strlen2d(line) - 1], " -> ");
	char *input;
	// ft_cd("../../");
	// // printf("%s\n", ft_pwd());
	while(1)
	{
		input = readline(prompt);
		ft_cd(input);
		printf("%s\n", ft_pwd());
	}
	// chdir("../../../../Desktop");
	// printf("%s\n",ft_pwd());
}