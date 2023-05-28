/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xi_haga.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:52:31 by hkasbaou          #+#    #+#             */
/*   Updated: 2023/05/28 17:38:05 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

void	dlt_herdoc_file(t_command **cmd)
{
	t_v	v;

	v.i = -1;
	while (cmd[++v.i]->ther)
	{
		v.j = -1;
		while (cmd[v.i]->cmd_parameter[++v.j] != NULL)
		{
			if (retu_if1(&v, cmd))
			{
				cmd[v.i]->cmd_parameter[v.j] = "";
				cmd[v.i]->cmd_parameter[v.j + 1] = "";
				v.j++;
			}
			if (retu_if2(&v, cmd))
			{
				cmd[v.i]->cmd_parameter[v.j] = "";
				cmd[v.i]->cmd_parameter[v.j + 1] = "";
				v.j++;
			}
		}
	}
}

int	chk_cmd_is_first_or_aftrederect(t_command **cmd, t_v *v)
{
	if (cmd[v->i]->cmd_parameter[0][0] == '>'
		|| cmd[v->i]->cmd_parameter[0][0] == '<'
		|| (cmd[v->i]->cmd_parameter[0][0] == '<'
			&& cmd[v->i]->cmd_parameter[0][1] == '<')
		|| (cmd[v->i]->cmd_parameter[0][0] == '>'
			&& cmd[v->i]->cmd_parameter[0][1] == '>'))
	{
		while (cmd[v->i]->cmd_parameter[v->j + 2] != NULL
			&& (cmd[v->i]->cmd_parameter[v->j][0] == '<'
			|| cmd[v->i]->cmd_parameter[v->j][0] == '>'))
		{
			if (cmd[v->i]->cmd_parameter[v->j + 1] == NULL)
				return (0);
			v->j += 2;
		}
		cmd[v->i]->cmd = cmd[v->i]->cmd_parameter[v->j];
		return (0);
	}
	else
	{
		cmd[v->i]->cmd = cmd[v->i]->cmd_parameter[0];
		return (0);
	}
	return (1);
}

void	rmplr_cmd(t_command **cmd)
{
	t_v		v;
	char	*ss;

	v.i = 0;
	v.j = 0;
	while (cmd[v.i]->ther)
	{
		v.j = 0;
		while (cmd[v.i]->cmd_parameter[v.j] != NULL)
		{
			if (!chk_cmd_is_first_or_aftrederect(cmd, &v))
				break ;
		}
		ss = rem_quots(cmd[v.i]->cmd);
		if (cmd[v.i]->cmd[0] == '<' || cmd[v.i]->cmd[0] == '>')
			cmd[v.i]->cmd = NULL;
		if (ss[0] == '\0')
			cmd[v.i]->cmd = ft_strdup("");
		v.i++;
	}
}

void	rmplr_parametr(t_command **cmd, char **splt)
{
	int	i;
	int	j;
	int	whr;
	int	k;

	i = 0;
	j = 0;
	whr = 0;
	k = 0;
	while (splt[i])
	{
		if (splt[i][0] != '|')
			cmd[k]->cmd_parameter[j++] = splt[i];
		else
		{
			cmd[k]->cmd_parameter[j] = NULL;
			j = 0;
			k++;
		}
		i++;
		if (splt[i] == NULL)
			cmd[k]->cmd_parameter[j] = NULL;
	}
}
