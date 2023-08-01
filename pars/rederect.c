/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:52:31 by hkasbaou          #+#    #+#             */
/*   Updated: 2023/05/28 18:35:31 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

int	infile_frst_enter(t_command **cmd, t_v *v)
{
	v->k = 0;
	v->j += 1;
	cmd[v->i]->infile = ft_malloc(2 * sizeof(t_file *), 1);
	if (!cmd[v->i]->infile)
		return (0);
	if (cmd[v->i]->cmd_parameter[v->j])
	{
		cmd[v->i]->infile[0] = ft_malloc(1 * sizeof(t_file), 1);
		cmd[v->i]->infile[1] = ft_malloc(1 * sizeof(t_file), 1);
		if (!cmd[v->i]->infile[0] || !cmd[v->i]->infile[1])
			return (0);
		if (cmd[v->i]->cmd_parameter[v->j - 1][0] == '<'
			&& cmd[v->i]->cmd_parameter[v->j - 1][1] == '<')
		{
			cmd[v->i]->herdoc = true;
			cmd[v->i]->infile[v->k]->mode = false;
		}
		else
			cmd[v->i]->infile[v->k]->mode = true;
		cmd[v->i]->infile[0]->file = cmd[v->i]->cmd_parameter[v->j];
		cmd[v->i]->infile[1] = NULL;
	}
	if (cmd[v->i]->cmd_parameter[v->j] == NULL)
		return (1);
	return (0);
}

int	chk_infile(t_command **cmd, t_v *v)
{
	if (cmd[v->i]->cmd_parameter[v->j][0] == '<')
	{
		if (cmd[v->i]->redirect_in == 0)
		{
			cmd[v->i]->redirect_in = 1;
			if (infile_frst_enter(cmd, v))
				return (1);
		}
		else
		{
			if (cmd[v->i]->cmd_parameter[v->j + 1])
			{
				v->j++;
				cmd[v->i]->infile = ft_strjoin_in(cmd[v->i]->infile,
						cmd[v->i]->cmd_parameter[v->j],
						cmd[v->i]->cmd_parameter[v->j - 1]);
			}
			if (cmd[v->i]->cmd_parameter[v->j] == NULL)
				return (1);
		}
	}
	return (0);
}

int	outfile_frst_enter(t_command **cmd, t_v *v)
{
	v->k = 0;
	v->j += 1;
	cmd[v->i]->outfile = ft_malloc(2 * sizeof(t_file *), 1);
	if (!cmd[v->i]->outfile)
		return (0);
	if (cmd[v->i]->cmd_parameter[v->j])
	{
		cmd[v->i]->outfile[0] = ft_malloc(1 * sizeof(t_file), 1);
		cmd[v->i]->outfile[1] = ft_malloc(1 * sizeof(t_file), 1);
		if (!cmd[v->i]->outfile[0] || !cmd[v->i]->outfile[1])
			return (0);
		if (cmd[v->i]->cmd_parameter[v->j - 1][0] == '>'
			&& cmd[v->i]->cmd_parameter[v->j - 1][1] == '>')
			cmd[v->i]->outfile[v->k]->mode = false;
		else
			cmd[v->i]->outfile[v->k]->mode = true;
		cmd[v->i]->outfile[0]->file = cmd[v->i]->cmd_parameter[v->j];
		cmd[v->i]->outfile[1] = NULL;
	}
	if (cmd[v->i]->cmd_parameter[v->j] == NULL)
		return (1);
	return (0);
}

int	chk_outfile(t_command **cmd, t_v *v)
{
	if (cmd[v->i]->cmd_parameter[v->j][0] == '>')
	{
		if (cmd[v->i]->redirect_out == 0)
		{
			cmd[v->i]->redirect_out = 1;
			if (outfile_frst_enter(cmd, v))
				return (1);
		}
		else
		{
			if (cmd[v->i]->cmd_parameter[v->j + 1])
			{
				v->j++;
				cmd[v->i]->outfile = ft_strjoin_out(cmd[v->i]->outfile,
						cmd[v->i]->cmd_parameter[v->j],
						cmd[v->i]->cmd_parameter[v->j - 1]);
			}
			if (cmd[v->i]->cmd_parameter[v->j] == NULL)
				return (1);
		}
	}
	return (0);
}

void	check_rederect(t_command **cmd)
{
	t_v	v;

	v.i = 0;
	v.j = 0;
	while (cmd[v.i]->ther)
	{
		v.j = 0;
		while (cmd[v.i]->cmd_parameter[v.j] != NULL)
		{
			v.k = 0;
			if (cmd[v.i]->cmd_parameter[v.j][0] == '<')
			{
				if (chk_infile(cmd, &v))
					break ;
			}
			else if (cmd[v.i]->cmd_parameter[v.j][0] == '>')
				if (chk_outfile(cmd, &v))
					break ;
			v.j++;
		}
		v.i++;
	}
}
