/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:18:08 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/24 16:48:03 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*join_expand_var(char *var, char *string, int index, \
t_global_info *g_info)
{
	if (!ft_strcmp(var, "?"))
		string = ft_strjoin(string, ft_itoa(g_info->exit_code));
	else if (index == -1)
		string = ft_strjoin(string, "");
	else
		string = ft_strjoin(string, \
		g_info->environ->variables[index].value);
	return (string);
}

char	*extract_var(char *expand_split, char *expand_string, \
t_global_info *g_info)
{
	int		j;
	int		var_index;
	char	*var_to_search;
	char	*rest;

	j = 0;
	if (ft_isalpha(expand_split[j]) || expand_split[j] == '_')
	{
		while (ft_isalnum(expand_split[j]) || expand_split[j] == '_')
			j++;
		var_to_search = ft_substr(expand_split, 0, j);
	}
	else
	{
		var_to_search = ft_substr(expand_split, 0, 1);
		j++;
	}
	var_index = search_in_env(g_info->environ, var_to_search);
	expand_string = join_expand_var(var_to_search, expand_string, \
	var_index, g_info);
	rest = ft_substr(expand_split, j, ft_strlen(expand_split) - j);
	expand_string = ft_strjoin(expand_string, rest);
	return (expand_string);
}

char	*expand_var(char *string, t_global_info *g_info)
{
	int		i;
	char	**expand_split;
	char	*expand_string;

	i = 0;
	expand_string = ft_strdup("");
	expand_split = ft_split(string, '$');
	if (ft_strlen(string) == 0)
		return (expand_string);
	if (string[0] != '$')
	{
		expand_string = ft_strjoin(expand_string, expand_split[0]);
		i++;
	}
	while (expand_split[i])
	{
		expand_string = extract_var(expand_split[i], expand_string, g_info);
		i++;
	}
	if (string[ft_strlen(string) - 1] == '$' && \
	string[ft_strlen(string) - 2] != '$')
		expand_string = ft_strjoin(expand_string, "$");
	return (expand_string);
}
