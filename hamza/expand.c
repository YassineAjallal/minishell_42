/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/18 17:05:10 by hkasbaou         ###   ########.fr       */
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
				// if(splt[i] == '$')
				// {
				// 	i++;
				// 	j = i;
				// 	while (splt[j] && (ft_isalnum(splt[j]) || splt[j] == '_'))
				// 		j++;
				// 	to_find = ft_substr(splt, i, j - i);
				// 	to_find = ft_strjoin_char(to_find, '=');
				// 	to_join = find_valr(to_find,g_info);
				// 	if(to_join)
				// 		str = ft_strjoin(str, to_join);
				// 	free(to_find);
				// 	to_find = NULL;
				// 	i = j;
				// 	if (splt[i] != '\0' && splt[i] != '"') 
				// 		str = ft_strjoin_char(str, splt[i]);
				// }
				// else
					str = ft_strjoin_char(str, splt[i]);
				// if(splt[i] != '$' && splt[i] != '\0' && splt[i] != '"')
					i++;
			}
		}
		if(splt[i] != '"' && splt[i] != '\'' && splt[i] != '\0')
		{
			// if(splt[i] == '$')
			// {
			// 	i++;
			// 	j = i;
			// 	while (splt[j] && (ft_isalnum(splt[j]) || splt[j] == '_'))
			// 		j++;
			// 	to_find = ft_substr(splt, i, j - i);
			// 	to_find = ft_strjoin_char(to_find, '=');
			// 	to_join = find_valr(to_find,g_info);
			// 	if(to_join)
			// 		str = ft_strjoin(str, to_join);
			// 	free(to_find);
			// 	to_find = NULL;
			// 	i = j;
			// 	if (splt[i] != '\0' && splt[i] != '"' && splt[i] != '\'')
			// 		str = ft_strjoin_char(str, splt[i]);
			// }
			// else
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
	// char **dup_splt;
	// char *str;
	// while (splt[i] != NULL) {
	// 	i++;
	// }
	// dup_splt = malloc((i + 1) * sizeof(char *));
	
	i = 0;
	while (splt[i]) {
		splt[i] = remove_quots(splt[i],g_info);
		printf("%s\n",splt[i]);
		// free(splt[i]);
		// splt[i] = str;
		// free(str);
		i++;
	}
	// dup_splt[i] = NULL;
	i = 0;
	// while (splt[i] != NULL) {
	// 	printf("%s\n",splt[i]);
	// 	i++;
	// }
	return splt;
}


int ft_strlen2d(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char **ft_strjoin_2d(char **s1, char *s2)
{
	int i;
	int j;
	char **new_array;
	
	i = 0;
	j = 0;
	new_array = malloc(sizeof(char *) * (ft_strlen2d(s1) + 2));
	if (!new_array)
		return (NULL);
	while(s1[i] && s1)
	{
		new_array[i] = ft_strdup(s1[i]);
		i++;
	}
	new_array[i] = ft_strdup(s2);
	i++;
	new_array[i] = NULL;
	return (new_array);
}
// size_t	ft_strlen_double(char **s)
// {
// 	size_t	i;
// 	if(!s)
// 		return 0;
// 	i = 0;
// 	while (s[i] != NULL)
// 		i++;
// 	return (i);
// }
// char	**ft_strjoin_double(char **s1, char *s2)
// {
// 	size_t	ttl;
// 	char	**str;
// 	size_t	i;
// 	int		j;
// 	i =  -1;
// 	j = 0;
// 	ttl = 1 + ft_strlen_double(s1);
// 	str = ft_calloc(ttl + 1, sizeof(char));
// 	if (!str || !s2 || !s1)
// 		return (NULL);
// 	while (s1[++i] != NULL) {
// 		str[i] = s1[i];
// 	}
// 	str[i++] = s2;
// 	str[i]= NULL;
// 	return (str);
// }
// int main(int ac ,char **av)
// {
// 	char **s ;
// 	int i = 0;
// 	s = ft_strjoin_double(s, "bonjour");
// 	if(!s)
// 		printf("HHH\n");
// }

char *rem_quots(char *splt)
{
	char *str = "";
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
				str = ft_strjoin_char(str, splt[i]);
				i++;
			}
		}
		if(splt[i] != '"' && splt[i] != '\'' && splt[i] != '\0')
		{
			str = ft_strjoin_char(str, splt[i]);
		}
		i++;
	}
	return str;
}

int check_empty(char *str)
{
	int i = 0;
	char *s = rem_quots(str);
	if(s[0] == '\0')
	{
		s = NULL;
		free(s);
		return 0;
	}
	s = NULL;
	free(s);
	return 1;
}
int  syntx_error_b(char **splt, t_global_info *g_info)
{
	int i = 0;
	int j = 0;
	while (splt[i]) {
		if(splt[i][0] == '>' || splt[i][0] == '<')
		{
			if(splt[i + 1] == NULL || splt[i + 1][0] == '|' || splt[i + 1][0] == '>' || splt[i + 1][0] == '<' || !check_empty(splt[i + 1]))
			{
				perror("SYNTAX ERROR");
				return 0;
			}
		}
		i++;
	}
	return 1;
}
int syntx_error_a(char **splt, t_global_info *g_info)
{
	int i = 0;
	int j = 0;
	while (splt[i]) {
		if(splt[i][0] == '|')
		{
			if(i == 0 ||!check_empty(splt[i - 1]))
			{
				perror("SYNTAX ERROR");
				return 0;
			}
			if(i != 0 && (splt[i + 1] == NULL ||!check_empty(splt[i + 1]) || splt[i + 1][0] =='|'))
			{
				perror("SYNTAX ERROR");
				return 0;
			}
		}
		i++;
	}
	return 1;
}