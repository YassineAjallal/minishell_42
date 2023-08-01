/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:16:01 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/30 15:28:43 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

int	quote1(char *str, t_v *v, char *line)
{
	v->quote = 0;
	v->s = str[v->i];
	line[v->j++] = str[v->i++];
	while (str[v->i] != v->s && str[v->i] != '\0')
	{
		line[v->j++] = str[v->i++];
	}
	if (str[v->i] == '\0')
		return (0);
	line[v->j++] = str[v->i++];
	return (1);
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
		s[i] = ft_malloc(1 * sizeof(t_file), 1);
		s[i] = s1[i];
		i++;
	}
	s[i] = NULL;
	return (s);
}
