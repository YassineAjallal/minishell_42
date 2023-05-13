/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/13 00:42:50 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../yassine/minishell.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strjoin_char(char const *s1, char s2)
{
	size_t	ttl;
	char	*str;
	size_t	i;
	int		j;

	i =  -1;
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

char	*ft_substr_ya(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			length;

	i = 0;
	length = ft_strlen(s);
	if (start >= length)
		return (ft_calloc(sizeof(char), 1));
	if (len >= length)
		len = length - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *find_valr(char *expn,t_global_info g_ifo)
{
	int i = 0;
	int j = 0;
	char *str;
	while (g_ifo.env_array[i]) {
		if(ft_strnstr(g_ifo.env_array[i], expn, ft_strlen(g_ifo.env_array[i])))
		{	
			while (g_ifo.env_array[i][j] != '=') {
				j++;
			}
			j++;
			str = ft_substr(g_ifo.env_array[i], j, ft_strlen(g_ifo.env_array[i]) - j);
			return str;
		}
		i++;
	}
	return NULL;
}

char *remove_quots(char *splt,t_global_info g_info)
{
	char *str = "";
	char *to_find;
	char *to_join;
	char qts;
	int i = 0;
	int j = 0;
	while (splt[i]) {
		if(splt[i] == '\'')
		{
			i++;
			while (splt[i] && splt[i] != '\'') {	
				str = ft_strjoin_char(str, splt[i]);
				i++;
			}
		}
		if(splt[i] == '"')
		{
			i++;
			while (splt[i] && splt[i] != '"') {	
				if(splt[i] == '$')
				{
					i++;
					j = i;
					while (splt[j] && (ft_isalnum(splt[j]) || splt[j] == '_'))
						j++;
					to_find = ft_substr(splt, i, j - i);
					to_find = ft_strjoin_char(to_find, '=');
					to_join = find_valr(to_find,g_info);
					if(to_join)
						str = ft_strjoin(str, to_join);
					free(to_find);
					to_find = NULL;
					i = j;
					if (splt[i] != '\0' && splt[i] != '"') 
						str = ft_strjoin_char(str, splt[i]);
				}
				else
					str = ft_strjoin_char(str, splt[i]);
				if(splt[i] != '$' && splt[i] != '\0' && splt[i] != '"')
					i++;
			}
		}
		if(splt[i] != '"' && splt[i] != '\'' && splt[i] != '\0')
		{
			if(splt[i] == '$')
			{
				i++;
				j = i;
				while (splt[j] && (ft_isalnum(splt[j]) || splt[j] == '_'))
					j++;
				to_find = ft_substr(splt, i, j - i);
				to_find = ft_strjoin_char(to_find, '=');
				to_join = find_valr(to_find,g_info);
				if(to_join)
					str = ft_strjoin(str, to_join);
				free(to_find);
				to_find = NULL;
				i = j;
				if (splt[i] != '\0' && splt[i] != '"' && splt[i] != '\'')
					str = ft_strjoin_char(str, splt[i]);
			}
			else
				str = ft_strjoin_char(str, splt[i]);
		}
		i++;
	}
	return str;
}



char **expand_splt(char **splt,t_global_info g_info)
{
	int i = 0;
	int j = 0;

	char **dup_splt;
	while (splt[i] != NULL) {
		i++;
	}
	dup_splt = malloc((i + 1) * sizeof(char *));
	
	i = 0;
	while (splt[i]) {
		dup_splt[i] = remove_quots(splt[i],g_info);
		i++;
	}
	dup_splt[i] = NULL;
	i = 0;
	while (dup_splt[i] != NULL) {
		printf("%s\n",dup_splt[i]);
		i++;
	}
	return dup_splt;
}
