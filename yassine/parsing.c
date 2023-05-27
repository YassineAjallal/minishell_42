/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:16:01 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 16:08:33 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_v
{
	int		i;
	int		j;
	int		k;
	int		cnt;
	int		size;
	int		quote;
	int		whr;
	char *str;
}			t_v;
char	*ft_strjoin_char(char const *s1, char s2)
{
	size_t	ttl;
	char	*str;
	size_t	i;
	int		j;

	i = -1;
	j = 0;
	ttl = ft_strlen(&s2) + ft_strlen(s1);
	str = ft_calloc(ttl + 1, sizeof(char));
	if (!str || !s2)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	str[i++] = s2;
	str[i++] = '\0';
	return (str);
}

void free_str_rmplr_tmp(t_v *v,char *tmp,char *splt,int k)
{
	tmp = ft_strjoin_char(v->str, splt[v->i]);
    free(v->str);
    v->str = tmp;
	if(k == 1)
		v->i++;
}
char *rem_quots(char *splt)
{
	char *tmp;
	t_v v;
	
	v.str = ft_strdup("");
	v.i = -1;
	while (splt[++v.i]) {
		if(splt[v.i] == '\'')
		{
			v.i++;
			while (splt[v.i] && splt[v.i] != '\'')
				free_str_rmplr_tmp(&v, tmp, splt,1);
		}
		if(splt[v.i] == '"')
		{
			v.i++;
			while (splt[v.i] && splt[v.i] != '"') 
				free_str_rmplr_tmp(&v, tmp, splt,1);
		}
		if(splt[v.i] != '"' && splt[v.i] != '\'' && splt[v.i] != '\0')
			free_str_rmplr_tmp(&v, tmp, splt,0);
	}
	return v.str;
}

int	check_empty(char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = rem_quots(str);
	if (s[0] == '\0')
		return (0);
	return (1);
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
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (splt[i])
	{
		if (splt[i][0] == '|')
		{
			if (i == 0)
			{
				ft_putstr_fd("minishell: syntax error\n",
								2);
				g_info->exit_code = 2;
				return (0);
			}
			if (i != 0 && (splt[i + 1] == NULL || splt[i + 1][0] == '|'))
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
