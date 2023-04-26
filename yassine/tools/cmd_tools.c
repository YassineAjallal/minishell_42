/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:41:51 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/26 18:43:51 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
void	ft_checkf(char *file, int ex)
{
	if (access(file, F_OK) < 0)
	{
		perror("minishell");
		exit(ex);
	}
}

int check_path_var(char **env)
{
	int		i;

	i = 0;
	while(env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (-1);
}

char *search_command(char *path_var, char *cmd)
{
	char *fpath;
	char **vars_split;
	char *addslash;
	int i;

	if (!path_var)
		return (NULL);
	vars_split = ft_split(path_var + 5, ':');
	while (vars_split[i])
	{
		addslash = ft_strjoin(vars_split[i], "/");
		fpath = ft_strjoin(addslash, cmd);
		if (access(fpath, F_OK) == 0)
		{
			ft_free2d(vars_split);
			free(addslash);
			return (fpath);
		}
		free(fpath);
		free(addslash);
		i++;
	}
	ft_free2d(vars_split);
	return (NULL);
}

char *cmd_path(char *cmd, char **env)
{
	char **env_vars;
	int path_var;
	char *fpath;
	int i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		ft_checkf(cmd, 0);
		return (cmd);
	}
	path_var = check_path_var(env);
	if (path_var == -1)
		return (NULL);
	printf("%d\n", path_var);
	fpath = search_command(env[path_var], cmd);
	return (fpath);
}

int main(int ac, char **av, char **env) {
    
	char *cmd;

	cmd =  cmd_path("cat", env);
	printf("%s\n", cmd);
    return 0;
}

