/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:16:01 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/16 18:55:22 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void syntax_error(char *input)
// {
// 	char **split_input;
// 	int i;

// 	split_input = ft_split(input, ' ');
// 	i = 0;
// 	if (!ft_strcmp(split_input[i], "|") || !ft_strcmp(split_input[i], "||"))
// 	{
// 		ft_putstr_fd("minishell: syntax error\n", 2);
// 		exit(258);
// 		// return;
// 	}
// 	while (split_input[i])
// 	{
// 		if (!ft_strcmp(split_input[i], ">") || !ft_strcmp(split_input[i], "<") 
// 			|| !ft_strcmp(split_input[i], "<<") || !ft_strcmp(split_input[i], ">>") || !ft_strcmp(split_input[i], "|") 
// 			|| !ft_strcmp(split_input[i], "||") )
// 		{
// 			i++;
// 			if (!split_input[i] ||
// 					!ft_strcmp(split_input[i], ">") || !ft_strcmp(split_input[i], "<") 
// 					|| !ft_strcmp(split_input[i], "<<") || !ft_strcmp(split_input[i], ">>") || !ft_strcmp(split_input[i], "|")
	
// 	 || !ft_strcmp(split_input[i], "||"))
// 			{
// 				ft_putstr_fd("minishell: syntax error\n", 2);
// 				exit(258);
// 				// return;
// 			}
// 		}	
// 		i++;	
// 	}
// }
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

char *rem_quots(char *splt)
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
		return 0;
	return 1;
}
int  syntx_error_b(char **splt, t_global_info *g_info)
{
	int i = 0;
	int j = 0;
	while (splt[i]) {
		if(splt[i][0] == '>' || splt[i][0] == '<')
		{
			if(splt[i + 1] == NULL || splt[i + 1][0] == '|' || splt[i + 1][0] == '>' || splt[i + 1][0] == '<' )
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				g_info->exit_code = 2;
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
			if(i == 0)
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				g_info->exit_code = 2;
				return 0;
			}
			if(i != 0 && (splt[i + 1] == NULL || splt[i + 1][0] =='|'))
			{
				ft_putstr_fd("minishell: syntax error\n", 2);
				g_info->exit_code = 2;
				return 0;
			}
		}
		i++;
	}
	return 1;
}
