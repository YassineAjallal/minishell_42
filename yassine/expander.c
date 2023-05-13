/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/13 10:29:40 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int search_in_env(t_env *env, char *string)
{
	int i;
	i = 0;
	while(i < env->nb_variables)
	{
		if (ft_strcmp(string, env->variables[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int next_dollar_pos(char *str, int pos)
{
	while (str[pos] == '$')
		pos++;
	while (str[pos])
	{
		if (str[pos] == '$')
			return (pos);
		pos++;
	}
	return (pos);
}

char *expand_var(char *string, t_global_info *g_info)
{
	int i;
	char **expand_split;
	int var_index;
	char *expand_string;
	char *var_to_search;
	int len;
	char *rest;
	char *tmp;
	int j;
	
	i = 0;
	expand_string = ft_strdup("");
	expand_split = ft_split(string, '$');
	len = ft_strlen(string);
	if (string[0] != '$')
	{
		tmp = ft_strjoin(expand_string, expand_split[0]);
		free(expand_string);
		expand_string = tmp;
		i++;
	}
	while(expand_split[i])
	{
		j = 0;
		if (ft_isalpha(expand_split[i][j]) || expand_split[i][j] == '_')
		{
			while(ft_isalnum(expand_split[i][j]) || expand_split[i][j] == '_')
				j++;
			var_to_search = ft_substr(expand_split[i], 0, j);
		}
		else
		{
			var_to_search = ft_substr(expand_split[i], 0, 1);
			j++;
		}
		var_index = search_in_env(g_info->environ, var_to_search);
		if (!ft_strcmp(var_to_search, "?"))
			tmp = ft_strjoin(expand_string, ft_itoa(g_info->exit_code));
		else if (var_index == -1)
			tmp = ft_strjoin(expand_string, "");
		else
			tmp = ft_strjoin(expand_string, g_info->environ->variables[var_index].value);
		free(expand_string);
		expand_string = tmp;
		rest = ft_substr(expand_split[i], j, ft_strlen(expand_split[i]) - j);
		tmp = ft_strjoin(expand_string, rest);
		free(expand_string);
		expand_string = tmp;
		i++;
	}
	if (string[len - 1] == '$' && string[len - 2] != '$')
	{
		tmp = ft_strjoin(expand_string, "$");
		free(expand_string);
		expand_string = tmp;
	}
	return (expand_string);
}

char *ft_expand(char *string, t_global_info *g_info)
{
	char *string_expand;
	char *tmp;
	if (string[0] != '\'')
	{
		tmp = ft_strtrim(string, "\"");
		free(string);
		string_expand = expand_var(tmp, g_info);
	}
	else
	{
		string_expand = ft_strtrim(string, "\'");
		free(string);
	}
	return (string_expand);
}
char **expand_all_param(t_command *cmd, t_global_info *g_info)
{
	int i;
	char **expanded_param;
	
	expanded_param = malloc(sizeof(char *) * (ft_strlen2d(cmd->cmd_parameter) + 1));
	i = 0;
	while(cmd->cmd_parameter[i])
	{
		expanded_param[i] = ft_expand(cmd->cmd_parameter[i], g_info);
		i++;
	}
	expanded_param[i] = NULL;
	// ft_free2d(cmd->cmd_parameter);
	cmd->cmd = ft_strdup(expanded_param[0]);
	return(expanded_param);
}

// int main(int ac, char **av, char **env)
// {
// 	t_global_info g_info;
// 	char *string;
// 	char *tmp;
// 	g_info.environ = dup_env(env);
// 	g_info.exit_code = 0;
// 	string = ft_strdup("1$USER-");
// 	printf("---------------  %s  -----------------\n\n\n", string);
// 	tmp = expand_var(string, &g_info);
// 	printf("%s\n", tmp);
// 	free(tmp);
// }