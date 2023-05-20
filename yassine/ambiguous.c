/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:38:13 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/20 14:36:15 by yajallal         ###   ########.fr       */
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

char *space_trim(char *file)
{
	int i;
	int j;
	char *new_file;
	int nb_space;
	
	i = 0;
	nb_space = 0;
	while(file[i])
	{
		if (file[i] == ' ')
			nb_space++;
		i++;
	}
	new_file = malloc(sizeof(char) * (ft_strlen(file) - nb_space + 1));
	i = 0;
	j = 0;
	while (file[i])
	{
		
		if (file[i] != ' ')
		{
			new_file[j] = file[i];
			j++;
		}
		i++;
	}
	new_file[j] = 0;
	return (new_file);
}

char **delete_empty_str(char **split_file)
{
	int calc_empty;
	char **new_file;
	int new_size;
	int i;
	int j;

	i = 0;
	j = 0;
	calc_empty = 0;
	while(split_file[i])
	{
		if ((int)ft_strlen(split_file[i]) == 0)
			calc_empty++;
		i++;
	}
	new_size = ft_strlen2d(split_file) - calc_empty;
	new_file = malloc(sizeof(char *) * (new_size + 1));
	if (!new_file)
		return (NULL);
	i = 0;
	while(split_file[i])
	{
		if ((int)ft_strlen(split_file[i]) != 0)
		{
			new_file[j] = ft_strdup(split_file[i]);
			j++;
		}
		i++;
	}
	new_file[j] = NULL;
	return (new_file);
}
char *ambiguous_redirect(char *file, t_global_info *g_info)
{
	int i;
	char **head_array;
	int old_lst;
	int new_lst;
	int len;
	t_expand *head;
	
	head = ft_expand(file);
	old_lst = lst_size(head);
	head = expand_linked_list(head, g_info);
	new_lst = lst_size(head);
	head = delete_empty(head);
	head_array = convert_linked_array(head);
	i = 0;
	len = ft_strlen(file) - 1;
	if (ft_strlen2d(head_array) == 0)
	{	
		if (new_lst == old_lst)
		{
			if (ft_strchr(file, '$'))
			{
				ft_putstr_fd("minishell: ambiguous redirect\n", 2);
				g_info->exit_code = 1;
				return (0);
			}
		}
		g_info->exit_code = 0;
		return (ft_strdup(""));
	}
	else if (ft_strlen2d(head_array) > 1)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		g_info->exit_code = 1;
		return (0);
	}
	// print(head);
	// printf("------------------\n");
	g_info->exit_code = 0;
	return (head_array[0]);
}
