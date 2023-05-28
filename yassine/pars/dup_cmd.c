/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:52:31 by hkasbaou          #+#    #+#             */
/*   Updated: 2023/05/28 17:47:46 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

t_command	**initialize_dup_cmd(t_command **cmd_rtr, int size)
{
	int	i;

	i = 0;
	cmd_rtr = ft_malloc((size) * sizeof(t_command *), 1);
	i = 0;
	while (i < size)
	{
		cmd_rtr[i] = ft_malloc(sizeof(t_command), 1);
		i++;
	}
	return (cmd_rtr);
}

t_command	**dup_cmd(t_command **cmd, t_command **cmd_rtr)
{
	int	i;

	i = 0;
	while (cmd[i]->ther)
	{
		cmd_rtr[i]->g_info = cmd[i]->g_info;
		cmd_rtr[i]->ther = cmd[i]->ther;
		cmd_rtr[i]->cmd = cmd[i]->cmd;
		cmd_rtr[i]->redirect_in = cmd[i]->redirect_in;
		cmd_rtr[i]->redirect_out = cmd[i]->redirect_out;
		cmd_rtr[i]->herdoc = cmd[i]->herdoc;
		cmd_rtr[i]->infile = cmd[i]->infile;
		cmd_rtr[i]->outfile = cmd[i]->outfile;
		cmd_rtr[i]->herdoc_stdout = cmd[i]->herdoc_stdout;
		i++;
	}
	cmd_rtr[i]->ther = 0;
	return (cmd_rtr);
}

void	dup_cmdrtr_prmtr(t_command **cmd_rtr, t_command **cmd)
{
	t_v	v;

	v.i = -1;
	v.cnt = 0;
	while (cmd[++v.i]->ther)
	{
		v.j = -1;
		v.cnt = 0;
		while (cmd[v.i]->cmd_parameter[++v.j] != NULL)
			if (cmd[v.i]->cmd_parameter[v.j][0] != '\0')
				v.cnt++;
		cmd_rtr[v.i]->cmd_parameter = ft_malloc((v.cnt + 1) * sizeof(char *),
				1);
		v.j = 0;
		v.cnt = 0;
		while (cmd[v.i]->cmd_parameter[v.j] != NULL)
		{
			if (cmd[v.i]->cmd_parameter[v.j][0] != '\0')
				cmd_rtr[v.i]->cmd_parameter[v.cnt++]
					= cmd[v.i]->cmd_parameter[v.j];
			v.j++;
		}
		cmd_rtr[v.i]->cmd_parameter[v.cnt] = NULL;
	}
}

t_command	**rmplr_double_str(t_command **cmd, t_global_info g_info, int size)
{
	int			j;
	int			i;
	t_command	**cmd_rtr;

	j = 0;
	i = 0;
	cmd_rtr = initialize_dup_cmd(cmd_rtr, size);
	dup_cmd(cmd, cmd_rtr);
	dup_cmdrtr_prmtr(cmd_rtr, cmd);
	i = 0;
	j = 0;
	return (cmd_rtr);
}

void	initlize_dup_cmd(t_command **cmd, t_global_info *g_info)
{
	t_v	v;

	v.i = 0;
	while (cmd[v.i]->ther != 0)
	{
		cmd[v.i]->redirect_in = 0;
		cmd[v.i]->redirect_out = 0;
		cmd[v.i]->herdoc = 0;
		cmd[v.i]->infile = NULL;
		cmd[v.i]->outfile = NULL;
		cmd[v.i]->herdoc_stdout = 0;
		cmd[v.i]->g_info = g_info;
		v.i++;
	}
}
