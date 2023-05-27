/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:41:51 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 12:14:16 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_executer.h"

int	check_path_var(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (-1);
}

char	*search_command(char *path_var, char *cmd)
{
	char	*fpath;
	char	**vars_split;
	char	*addslash;
	int		i;

	if (!path_var)
		return (NULL);
	i = 0;
	vars_split = ft_split(path_var + 5, ':');
	while (vars_split[i])
	{
		addslash = ft_strjoin(vars_split[i], "/");
		fpath = ft_strjoin(addslash, cmd);
		if (access(fpath, F_OK) == 0)
		{
			return (fpath);
		}
		i++;
	}
	return (NULL);
}

char	*cmd_path(t_command *cmd)
{
	int		path_var;
	char	*fpath;
	int		i;

	i = 0;
	if (ft_strlen(cmd->cmd) == 0)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		return (NULL);
	}
	if (ft_strchr(cmd->cmd, '/'))
	{
		if (!ft_checkf(cmd->cmd))
			return (NULL);
		return (cmd->cmd);
	}
	path_var = check_path_var(cmd->g_info->env_array);
	if (path_var == -1)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		return (NULL);
	}
	fpath = search_command(cmd->g_info->env_array[path_var], cmd->cmd);
	if (!fpath)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		return (NULL);
	}
	return (fpath);
}

int	cmd_validation(t_command *cmd)
{
	if (!cmd->cmd)
	{
		cmd->g_info->exit_code = 0;
		return (0);
	}
	cmd->command_path = cmd_path(cmd);
	if (!cmd->command_path)
	{
		cmd->g_info->exit_code = 127;
		return (0);
	}
	if (!ft_checkx(cmd->command_path))
	{
		cmd->g_info->exit_code = 126;
		return (0);
	}
	cmd->g_info->exit_code = 0;
	return (1);
}
