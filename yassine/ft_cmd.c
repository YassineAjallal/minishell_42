/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 02:20:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/01/25 15:43:21 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	**ft_envp(char **envp)
{
	char	**paths;
	char	*dpath;
	int		i;

	dpath = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:.";
	i = 0;
	if (!envp[i])
	{
		paths = ft_split(dpath, ':');
		return (paths);
	}
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*ft_cmd(char **paths, char *cmd)
{
	char	*fpath;
	char	*addslash;
	int		i;

	i = 0;
	while (paths[i] && paths)
	{
		addslash = ft_strjoin(paths[i], "/");
		fpath = ft_strjoin(addslash, cmd);
		if (access(fpath, F_OK) == 0)
		{
			ft_free2d(paths, addslash);
			return (fpath);
		}
		ft_free(fpath, addslash);
		i++;
	}
	ft_free2d(paths, NULL);
	return (0);
}

char	*ft_cmdpath(char *cmd, char **envp)
{
	char	**paths;
	char	*fpath;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
	{
		ft_checkf(cmd, "pipex: no such file or directory:", 0);
		return (cmd);
	}
	paths = ft_envp(envp);
	fpath = ft_cmd(paths, cmd);
	return (fpath);
}

char	**ft_quotes(char *cmd)
{
	char	c;
	char	**quotes;
	int		i;

	i = 0;
	c = 0;
	while (cmd[i])
	{
		if (cmd[i] == 39 || cmd[i] == 34)
		{
			c = cmd[i];
			break ;
		}
		i++;
	}
	if (c != 0)
	{
		quotes = ft_split(cmd, c);
		quotes[0] = ft_strtrim(quotes[0], " ");
	}
	else
		quotes = ft_split(cmd, ' ');
	return (quotes);
}
