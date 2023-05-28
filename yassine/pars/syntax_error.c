/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:16:01 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/28 17:38:18 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

void	free_str_rmplr_tmp(t_v *v, char *tmp, char *splt, int k)
{
	tmp = ft_strjoin_char(v->str, splt[v->i]);
	v->str = tmp;
	if (k == 1)
		v->i++;
}

char	*rem_quots(char *splt)
{
	char	*tmp;
	t_v		v;

	v.str = ft_strdup("");
	v.i = -1;
	while (splt[++v.i])
	{
		if (splt[v.i] == '\'')
		{
			v.i++;
			while (splt[v.i] && splt[v.i] != '\'')
				free_str_rmplr_tmp(&v, tmp, splt, 1);
		}
		if (splt[v.i] == '"')
		{
			v.i++;
			while (splt[v.i] && splt[v.i] != '"')
				free_str_rmplr_tmp(&v, tmp, splt, 1);
		}
		if (splt[v.i] != '"' && splt[v.i] != '\'' && splt[v.i] != '\0')
			free_str_rmplr_tmp(&v, tmp, splt, 0);
	}
	return (v.str);
}

int	syntx_error_b(char **splt, t_global_info *g_info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (splt[i])
	{
		if (splt[i][0] == '>' || splt[i][0] == '<')
		{
			if (splt[i + 1] == NULL || splt[i + 1][0] == '|' || splt[i
				+ 1][0] == '>' || splt[i + 1][0] == '<')
			{
				ft_putstr_fd("minishell: syntax error\n",
					2);
				g_info->exit_code = 2;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	syntx_error_a(char **splt, t_global_info *g_info)
{
	t_v	v;

	v.i = -1;
	while (splt[++v.i])
	{
		if (splt[v.i][0] == '|')
		{
			if (v.i == 0)
			{
				ft_putstr_fd("minishell: syntax error\n",
					2);
				g_info->exit_code = 2;
				return (0);
			}
			if (v.i != 0 && (splt[v.i + 1] == NULL || splt[v.i + 1][0] == '|'))
			{
				ft_putstr_fd("minishell: syntax error\n",
					2);
				g_info->exit_code = 2;
				return (0);
			}
		}
	}
	return (1);
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
