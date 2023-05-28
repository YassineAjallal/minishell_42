/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:16:01 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/28 23:19:44 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

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
}

// int	els_if(char *s, t_v *v, char *line, t_global_info *g_info)
// {
// 	int l;
	
// 	if (s[v->i] == ' ')
// 	{
// 		line[v->j++] = '\n';
// 		v->i++;
// 	}
// 	else if ((s[v->i] == '<' && s[v->i + 1] == '<') || (s[v->i] == '>' && s[v->i
// 				+ 1] == '>'))
// 		lxr_add_two(s, v, line);
// 	else if (s[v->i] == '|' || s[v->i] == '>' || s[v->i] == '<')
// 		lxr_add_one(s, v, line);
// 	else if (s[v->i] == '"' || s[v->i] == '\'')
// 	{
// 		quote(s, v, line);
// 		if (v->quote != -1)
// 		{
// 			rtr_err_quots(g_info, line);
// 			return (0);
// 		}
// 		line[v->j++] = '\n';
// 	}
// 	else
// 		line[v->j++] = s[v->i++];
// 	return (1);
// }
int	els_if(char *s, t_v *v, char *line, t_global_info *g_info)
{
	int l;
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
		l = quote1(s, v, line);
		if (l == 0)
		{
			rtr_err_quots(g_info, line);
			return (0);
		}
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
	line = ft_malloc(sizeof(char) * (ft_strlen(str) * 2), 1);
	while (str[v.i])
	{
		if (!els_if(str, &v, line, g_info))
			return (NULL);
	}
	line[v.j] = 0;
	splt = ft_split(line, '\n');
	return (splt);
}
