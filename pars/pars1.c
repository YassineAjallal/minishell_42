/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:52:31 by hkasbaou          #+#    #+#             */
/*   Updated: 2023/05/28 18:33:54 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

void	initialize_cmd(t_command **cmd, t_global_info *g_info, char **splt)
{
	t_v	v;
	int	strt;

	v.i = -1;
	v.whr = 0;
	strt = 0;
	while (splt[++v.i] != NULL)
	{
		if (strt == 0)
		{
			cmd[v.whr]->ther = 1;
			strt = 1;
			v.whr++;
		}
		if (splt[v.i][0] == '|')
			strt = 0;
	}
	cmd[v.whr]->ther = 0;
	initlize_dup_cmd(cmd, g_info);
}

void	mlc_cmd_paramt(t_command **cmd, char **splt)
{
	t_v	v;
	int	stop;

	v.i = -1;
	v.whr = 0;
	stop = 0;
	while (splt[++v.i] != NULL)
	{
		v.k = v.i;
		v.cnt = 0;
		while (splt[v.k][0] != '|')
		{
			v.cnt++;
			v.k++;
			if (splt[v.k] == NULL)
				break ;
		}
		cmd[v.whr]->cmd_parameter = ft_malloc(sizeof(char *) * (v.cnt + 1), 1);
		if (!cmd[v.whr]->cmd_parameter)
			return ;
		v.i = v.k;
		if (splt[v.i] == NULL)
			break ;
		v.whr++;
	}
}

t_command	**alloc_cmd_nb_pipe(t_command **cmd, t_global_info *g_info, t_v *v,
		char **splt)
{
	v->i = 0;
	v->j = 0;
	v->cnt = 0;
	while (splt[v->i] != NULL)
	{
		if (splt[v->i][v->j] == '|')
			v->cnt++;
		v->i++;
	}
	cmd = ft_malloc((v->cnt + 2) * sizeof(t_command *), 1);
	if (!cmd)
		return (NULL);
	v->size = v->cnt + 2;
	g_info->nb_pipe = v->cnt;
	return (cmd);
}

t_command	**rmplir_strct(char **splt, t_global_info *g_info)
{
	t_command	**cmd;
	t_command	**cmd_rtr;
	t_v			v;

	cmd = NULL;
	cmd = alloc_cmd_nb_pipe(cmd, g_info, &v, splt);
	v.i = 0;
	while (v.i < v.cnt + 2)
	{
		cmd[v.i] = ft_malloc(sizeof(t_command), 1);
		if (!cmd[v.i])
			return (NULL);
		v.i++;
	}
	initialize_cmd(cmd, g_info, splt);
	mlc_cmd_paramt(cmd, splt);
	rmplr_parametr(cmd, splt);
	rmplr_cmd(cmd);
	check_rederect(cmd);
	dlt_herdoc_file(cmd);
	cmd_rtr = rmplr_double_str(cmd, v.size);
	return (cmd_rtr);
}
