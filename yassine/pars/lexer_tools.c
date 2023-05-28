/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:16:01 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/28 16:52:14 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

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
		s[i] = ft_malloc(1 * sizeof(t_file),1);
		s[i] = s1[i];
		i++;
	}
	s[i] = NULL;
	return (s);
}