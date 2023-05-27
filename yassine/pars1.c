/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:52:31 by hkasbaou          #+#    #+#             */
/*   Updated: 2023/05/27 15:50:46 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include <stdlib.h>

typedef struct s_v
{
	int		i;
	int		j;
	int		k;
	int		cnt;
	int		size;
	int		quote;
	int		whr;
}			t_v;

char	**ft_strjoin_2d(char **s1, char *s2)
{
	int		i;
	int		j;
	char	**new_array;

	i = 0;
	j = 0;
	new_array = malloc(sizeof(char *) * (ft_strlen2d(s1) + 2));
	if (!new_array)
		return (NULL);
	while (s1[i] && s1)
	{
		new_array[i] = ft_strdup(s1[i]);
		i++;
	}
	new_array[i] = ft_strdup(s2);
	i++;
	new_array[i] = NULL;
	return (new_array);
}

int	ft_strlen_out(t_file **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_file	**ft_strjoin_out(t_file **s1, char *s2, char *mode)
{
	int		i;
	int		j;
	t_file	**new_array;

	i = 0;
	j = 0;
	new_array = malloc(sizeof(t_file *) * (ft_strlen_out(s1) + 2));
	if (!new_array)
		return (NULL);
	while (s1[i] && s1)
	{
		new_array[i] = malloc(1 * sizeof(t_file));
		new_array[i]->file = s1[i]->file;
		new_array[i]->mode = s1[i]->mode;
		i++;
	}
	new_array[i] = malloc(1 * sizeof(t_file));
	new_array[i]->file = s2;
	if ((mode[0] == '>' && mode[1] == '>'))
		new_array[i]->mode = false;
	else if (mode[0] == '>')
		new_array[i]->mode = true;
	i++;
	new_array[i] = NULL;
	return (new_array);
}

t_file	**ft_strjoin_in(t_file **s1, char *s2, char *mode)
{
	int		i;
	int		j;
	t_file	**new_array;

	i = 0;
	j = 0;
	new_array = malloc(sizeof(t_file *) * (ft_strlen_out(s1) + 2));
	if (!new_array)
		return (NULL);
	while (s1[i] && s1)
	{
		new_array[i] = malloc(1 * sizeof(t_file));
		new_array[i]->file = s1[i]->file;
		new_array[i]->mode = s1[i]->mode;
		i++;
	}
	new_array[i] = malloc(1 * sizeof(t_file));
	new_array[i]->file = s2;
	if ((mode[0] == '<' && mode[1] == '<'))
		new_array[i]->mode = false;
	else if (mode[0] == '<')
		new_array[i]->mode = true;
	i++;
	new_array[i] = NULL;
	return (new_array);
}

void	quots_initialize(char *str, t_v *v)
{
	if (str[v->i] == '"')
		v->quote = 1;
	else if (str[v->i] == '\'')
		v->quote = 2;
	else
		v->quote = -1;
}

void	quote(char *str, t_v *v, char *line)
{
	v->quote = 0;
	while (1)
	{
		quots_initialize(str, v);
		line[v->j++] = str[v->i++];
		while ((v->quote == 1 || v->quote == 2) && str[v->i] != '\0')
		{
			if (str[v->i] == '"' && v->quote == 1)
			{
				v->quote = -1;
				break ;
			}
			if (str[v->i] == '\'' && v->quote == 2)
			{
				v->quote = -1;
				break ;
			}
			line[v->j++] = str[v->i++];
		}
		line[v->j++] = str[v->i++];
		if (str[v->i] == ' ' || str[v->i] == '>' || str[v->i] == '\0'
			|| str[v->i - 1] == '\0')
			break ;
	}
}

void	lxr_add_two(char *str, t_v *v, char *line)
{
	line[v->j++] = '\n';
	line[v->j++] = str[v->i];
	line[v->j++] = str[v->i + 1];
	line[v->j++] = '\n';
	v->i += 2;
}

void	lxr_add_one(char *str, t_v *v, char *line)
{
	line[v->j++] = '\n';
	line[v->j++] = str[v->i++];
	line[v->j++] = '\n';
}

void	rtr_err_quots(t_global_info *g_info, char *line)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching\n", 2);
	g_info->exit_code = 2;
	free(line);
}

int	els_if(char *s, t_v *v, char *line, t_global_info *g_info)
{
	if (s[v->i] == ' ')
	{
		line[v->j++] = '\n';
		v->i++;
	}
	else if ((s[v->i] == '<' && s[v->i + 1] == '<') || (s[v->i] == '>' && s[v->i
				+ 1] == '>'))
		lxr_add_two(s, v, line);
	else if (s[v->i] == '|' || s[v->i] == '>' || s[v->i] == '<')
		lxr_add_one(s, v, line);
	else if (s[v->i] == '"' || s[v->i] == '\'')
	{
		quote(s, v, line);
		if (v->quote != -1)
		{
			rtr_err_quots(g_info, line);
			return (0);
		}
		line[v->j++] = '\n';
	}
	else
		line[v->j++] = s[v->i++];
	return (1);
}

char	**lexer(char *str, t_global_info *g_info)
{
	t_v		v;
	char	*line;
	char	**splt;

	v.i = 0;
	v.j = 0;
	v.k = 0;
	v.quote = 0;
	line = malloc(sizeof(char) * (ft_strlen(str) * 2));
	while (str[v.i])
	{
		if (!els_if(str, &v, line, g_info))
			return (NULL);
	}
	line[v.j] = 0;
	splt = ft_split(line, '\n');
	free(line);
	return (splt);
}

t_file	**ft_strdup_file(t_file **s1)
{
	size_t	i;
	t_file	**s;

	if (ft_strlen_out(s1) == 0)
	{
		return (NULL);
	}
	s = ft_calloc(ft_strlen_out(s1) + 1, sizeof(t_file *));
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = malloc(1 * sizeof(t_file));
		s[i] = s1[i];
		i++;
	}
	s[i] = NULL;
	return (s);
}

t_command	**initialize_dup_cmd(t_command **cmd_rtr, int size)
{
	int	i;

	i = 0;
	cmd_rtr = malloc((size) * sizeof(t_command *));
	i = 0;
	while (i < size)
	{
		cmd_rtr[i] = malloc(sizeof(t_command));
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
		{
			if (cmd[v.i]->cmd_parameter[v.j][0] != '\0')
				v.cnt++;
		}
		cmd_rtr[v.i]->cmd_parameter = malloc((v.cnt + 1) * sizeof(char *));
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

int	infile_frst_enter(t_command **cmd, t_v *v)
{
	cmd[v->i]->redirect_in = 1;
	v->k = 0;
	v->j += 1;
	cmd[v->i]->infile = malloc(2 * sizeof(t_file *));
	if (cmd[v->i]->cmd_parameter[v->j])
	{
		cmd[v->i]->infile[0] = malloc(1 * sizeof(t_file));
		cmd[v->i]->infile[1] = malloc(1 * sizeof(t_file));
		if (cmd[v->i]->cmd_parameter[v->j - 1][0] == '<'
			&& cmd[v->i]->cmd_parameter[v->j - 1][1] == '<')
		{
			cmd[v->i]->herdoc = true;
			cmd[v->i]->infile[v->k]->mode = false;
		}
		else
			cmd[v->i]->infile[v->k]->mode = true;
		cmd[v->i]->infile[0]->file = cmd[v->i]->cmd_parameter[v->j];
		free(cmd[v->i]->infile[1]);
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
			{
				return (1);
			}
		}
	}
	return (0);
}

int	outfile_frst_enter(t_command **cmd, t_v *v)
{
	cmd[v->i]->redirect_out = 1;
	v->k = 0;
	v->j += 1;
	cmd[v->i]->outfile = malloc(2 * sizeof(t_file *));
	if (cmd[v->i]->cmd_parameter[v->j])
	{
		cmd[v->i]->outfile[0] = malloc(1 * sizeof(t_file));
		cmd[v->i]->outfile[1] = malloc(1 * sizeof(t_file));
		if (cmd[v->i]->cmd_parameter[v->j - 1][0] == '>'
			&& cmd[v->i]->cmd_parameter[v->j - 1][1] == '>')
			cmd[v->i]->outfile[v->k]->mode = false;
		else
			cmd[v->i]->outfile[v->k]->mode = true;
		cmd[v->i]->outfile[0]->file = cmd[v->i]->cmd_parameter[v->j];
		free(cmd[v->i]->outfile[1]);
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

int	retu_if1(t_v *v, t_command **cmd)
{
	if (((cmd[v->i]->cmd_parameter[v->j][0] == '>'
			&& cmd[v->i]->cmd_parameter[v->j][1] == '>')
		|| (cmd[v->i]->cmd_parameter[v->j][0] == '<'
				&& cmd[v->i]->cmd_parameter[v->j][1] == '<'))
		&& cmd[v->i]->cmd_parameter[v->j + 1] != NULL)
		return (1);
	return (0);
}

int	retu_if2(t_v *v, t_command **cmd)
{
	if ((cmd[v->i]->cmd_parameter[v->j][0] == '>'
		|| cmd[v->i]->cmd_parameter[v->j][0] == '<')
			&& cmd[v->i]->cmd_parameter[v->j + 1] != NULL)
		return (1);
	return (0);
}

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
		free(ss);
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
		cmd[v.whr]->cmd_parameter = malloc(sizeof(char *) * (v.cnt + 1));
		v.i = v.k;
		if (splt[v.i] == NULL)
			break ;
		v.whr++;
	}
}

void	free_cmd(t_command **cmd)
{
	int	i;

	i = 0;
	while (cmd[i]->ther)
	{
		free(cmd[i]->cmd_parameter);
		free(cmd[i]);
		i++;
	}
	free(cmd[i]);
	free(cmd);
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
	cmd = malloc((v->cnt + 2) * sizeof(t_command *));
	v->size = v->cnt + 2;
	g_info->nb_pipe = v->cnt;
	return (cmd);
}

t_command	**rmplir_strct(char **splt, t_global_info *g_info)
{
	t_command	**cmd;
	t_command	**cmd_rtr;
	t_v			v;

	cmd = alloc_cmd_nb_pipe(cmd, g_info, &v, splt);
	v.i = 0;
	while (v.i < v.cnt + 2)
		cmd[v.i++] = malloc(sizeof(t_command));
	initialize_cmd(cmd, g_info, splt);
	mlc_cmd_paramt(cmd, splt);
	rmplr_parametr(cmd, splt);
	rmplr_cmd(cmd);
	check_rederect(cmd);
	dlt_herdoc_file(cmd);
	cmd_rtr = rmplr_double_str(cmd, *g_info, v.size);
	free_cmd(cmd);
	return (cmd_rtr);
}

int	error_redirect(char **splt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (splt[i] != NULL)
	{
		printf("{{%s}}\n", splt[i]);
		if (splt[i][0] == '<' || splt[i][0] == '>')
		{
			printf("$$  %s  $$\n", splt[i + 1]);
			if (splt[i + 1] == NULL)
				return (0);
			if (splt[i + 1][0] == '<' || splt[i + 1][0] == '>')
				return (0);
		}
		i++;
	}
	return (1);
}
