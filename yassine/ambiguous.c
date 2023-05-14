/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:38:13 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/14 20:20:12 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int var_value(char *string, t_global_info *g_info)
// {
// 	int i;
// 	char **expand_split;
// 	int var_index;
// 	char *var_to_search;
// 	int j;
	
// 	i = 0;
// 	expand_split = ft_split(string, '$');
// 	if (string[0] != '$')
// 		i++;
// 	while(expand_split[i])
// 	{
// 		j = 0;
// 		if (ft_isalpha(expand_split[i][j]) || expand_split[i][j] == '_')
// 		{
// 			while(ft_isalnum(expand_split[i][j]) || expand_split[i][j] == '_')
// 				j++;
// 			var_to_search = ft_substr(expand_split[i], 0, j);
// 		}
// 		else
// 		{
// 			var_to_search = ft_substr(expand_split[i], 0, 1);
// 			j++;
// 		}
// 		var_index = search_in_env(g_info->environ, var_to_search);
// 		if (ft_strchr(g_info->environ->variables[var_index].value, ' '))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int calc_until_pipe(char **split, int *pos)
// {
// 	int i;

// 	i = 0;
// 	while(split[*pos] && !ft_strcmp(split[*pos], "|"))
// 	{
// 		*pos++;
// 		i++;
// 	}
// 	return (i);
// }
// void original_input(char *split, t_global_info *g_info, t_command **cmd)
// {
// 	int i;
// 	int j;
// 	int pos;
// 	int len;
	
// 	i = 0;
// 	pos = 0;
// 	while(i < g_info->nb_pipe + 1)
// 	{
// 		len = calc_until_pipe(split, &pos);
// 		cmd[i]->original_input = malloc(sizeof(char *) * (len + 1));
// 		j = 0;
// 		// while()
// 	}
// }
int calc_space(char *file)
{
	int i;
	int spaces;

	i = 0;
	spaces = 0;
	while(file[i])
	{
		if (file[i] == ' ')
			spaces++;
		i++;
	}
	return (spaces);
}
int ambiguous_redirect(char *file, t_global_info *g_info)
{
	int nb_spaces;
	char *tmp;
	int nb_spaces_expand;
	char *expand_file;

	tmp = ft_strtrim(file, " ");
	free(file);
	file = tmp;
	nb_spaces = calc_space(file);
	// expand_file = ft_expand(file, g_info);
	
	// if (!ft_strchr(file, '$'))
	// 	return(1);
	if (ft_strlen(expand_file) == 0)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		return (0);
	}
	if (expand_file[0] != ' ')
	{	
		tmp = ft_strtrim(expand_file, " ");
		free(expand_file);
		expand_file = tmp;
		nb_spaces_expand = calc_space(expand_file);
		if (nb_spaces_expand == nb_spaces)
			return (1);
		else
		{
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
			return (0);
		}
	}
	nb_spaces_expand = calc_space(expand_file);
	if (nb_spaces_expand > nb_spaces)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		return (0);
	}
	return (1);
}
