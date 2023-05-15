/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/15 13:21:09 by yajallal         ###   ########.fr       */
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

char *space_trim(char *str)
{
	int i;
	char **split_space;
	char *string_trim;
	char *tmp;

	i = 0;
	split_space = ft_split(str, ' ');
	if (ft_strlen(str) > 0 && ft_strlen2d(split_space) == 0)
	{
		string_trim = ft_strdup(" ");
		return (string_trim);
	}
	while(split_space[i])
	{
		tmp = ft_strjoin(string_trim, split_space[i]);
		free(string_trim);
		string_trim = tmp;
		if (split_space[i + 1])
		{
			tmp = ft_strjoin(string_trim, " ");
			free(string_trim);
			string_trim = tmp;
		}
		i++;
	}
	if (str[0] == ' ')
	{
		tmp = ft_strjoin(" ", string_trim);
		free(string_trim);
		string_trim = tmp;
	}
	if (str[ft_strlen(str) - 1] == ' ')
	{
		tmp = ft_strjoin(string_trim, " ");
		free(string_trim);
		string_trim = tmp;
	}
	return (string_trim);
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
	if (ft_strlen(string) == 0)
		return (expand_string);
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
		// printf("rest : %s\n", rest);
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

// char *ft_expand(char *string, t_global_info *g_info)
// {
// 	char *string_expand;
// 	char *tmp;
// 	if (string[0] != '\'')
// 	{
// 		tmp = ft_strtrim(string, "\"");
// 		// free(string);
// 		string_expand = expand_var(tmp, g_info);
// 	}
// 	else
// 	{
// 		string_expand = ft_strtrim(string, "\'");
// 		// free(string);
// 	}
// 	return (string_expand);
// }
// char **check_expand_only(char *string)
// {
// 	int i;
// 	int nb_dollar;
// 	char **expand;

// 	i = 0;
// 	nb_dollar = 0;

// 	expand = ft_split(string);
// 	while(string[i])
// 	{
// 		if (string[i] == '$')
// 			nb_dollar++;
// 	}
// }
char **ft_strjoin2d(char **s1, char **s2)
{
	int i;
	int j;
	char **new_array;
	
	i = 0;
	j = 0;
	new_array = malloc(sizeof(char *) * (ft_strlen2d(s1) + ft_strlen2d(s2) + 1));
	if (!new_array)
		return (NULL);
	while(s1[i] && s1)
	{
		// printf("s1 : %s-->\n", s1[i]);
		new_array[i] = ft_strdup(s1[i]);
		i++;
	}
	while(s2[j] && s2)
	{
		new_array[i] = ft_strdup(s2[j]);
		// printf("s2 : %s-->\n", s2[j]);
		i++;
		j++;
	}
	new_array[i] = NULL;
	// ft_free2d(s1);
	// ft_free2d(s2);
	return (new_array);
}

char **strjoin2d_string(char **s1, char *s2)
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
	// ft_free2d(s1);
	// free(s2);
	return (new_array);
}

char **ft_expand(char *string, t_global_info *g_info)
{
	int i;
	int j;
	char **new_cmd_param;
	char *tmp;
	char *expand_without_q;
	char **no_qoutes;
	char **param_tmp;
	char *expand_double_q;
	int pos;

	i = 0;
	new_cmd_param = malloc(sizeof(char *));
	if (!new_cmd_param)
		return (NULL);
	new_cmd_param[0] = NULL;
	while(string[i])
	{
		if (string[i] == '\"')
		{
			i++;
			pos = i;
			while(string[i] != '\"' && string[i])
				i++;
			if (string[i] == '\"')
				i++;
			tmp = ft_substr(string, pos, i - pos - 1);
			expand_double_q = expand_var(tmp, g_info);
			if (expand_without_q[ft_strlen(expand_without_q) - 1] != ' ')
			{
				tmp = ft_strjoin(new_cmd_param[ft_strlen2d(new_cmd_param) - 1], expand_double_q);
				free(new_cmd_param[ft_strlen2d(new_cmd_param) - 1]);
				new_cmd_param[ft_strlen2d(new_cmd_param) - 1] = tmp;
			}
			else
			{
				param_tmp = strjoin2d_string(new_cmd_param, expand_double_q);
				ft_free2d(new_cmd_param);
				new_cmd_param = param_tmp;
			}
		}
		else if (string[i] == '\'')
		{
			i++;
			pos = i;
			while(string[i] != '\'' && string[i])
				i++;
			if (string[i] == '\'')
				i++;
			expand_double_q = ft_substr(string, pos, i - pos - 1);
			if (expand_without_q[ft_strlen(expand_without_q) - 1] != ' ')
			{
				tmp = ft_strjoin(new_cmd_param[ft_strlen2d(new_cmd_param) - 1], expand_double_q);
				free(new_cmd_param[ft_strlen2d(new_cmd_param) - 1]);
				new_cmd_param[ft_strlen2d(new_cmd_param) - 1] = tmp;
			}
			else
			{
				param_tmp = strjoin2d_string(new_cmd_param, expand_double_q);
				ft_free2d(new_cmd_param);
				new_cmd_param = param_tmp;
			}
		}
		else
		{
			pos = i;
			while(string[i] != '\"' && string[i] != '\'' && string[i])
				i++;
			tmp = ft_substr(string, pos, i);
			// printf("tmp : %s\n", tmp);
			expand_without_q = expand_var(tmp, g_info);
			// printf("%s-->\n", expand_without_q);
			no_qoutes = ft_split(expand_without_q, ' ');
			if (ft_strlen2d(no_qoutes) == 1)
				param_tmp = strjoin2d_string(new_cmd_param, expand_without_q);
			else
				param_tmp = ft_strjoin2d(new_cmd_param, no_qoutes);
			// printf("---------------from ft_expand---------------\n");
			ft_free2d(new_cmd_param);
			new_cmd_param = param_tmp;
		}
	}
	// int k;
	// k = 0;
	// while(new_cmd_param[k])
	// {
	// 	printf("%s\n", new_cmd_param[k]);
	// 	k++;
	// }
	return (new_cmd_param);
}

char **expand_all_param(t_command *cmd, t_global_info *g_info)
{
	int i;
	char **expanded_param;
	char **tmp;
	char **exp;
	expanded_param = malloc(sizeof(char *));
	if (!expanded_param)
		return (NULL);
	expanded_param[0] = NULL;
	i = 0;
	while(cmd->cmd_parameter[i])
	{
		exp = ft_expand(cmd->cmd_parameter[i], g_info);
		// printf("%s\n", cmd->cmd_parameter[i]);
		tmp = ft_strjoin2d(expanded_param, exp);
		// printf("------------------------------\n");
		// int k;
		// k = 0;
		// while(exp[k])
		// {
		// 	printf("%s\n", exp[k]);
		// 	k++;
		// }
		free(expanded_param);
		expanded_param = tmp;
		i++;
	}
	// expanded_param[i] = NULL;
	cmd->cmd = ft_strdup(expanded_param[0]);
	ft_free2d(cmd->cmd_parameter);
	return(expanded_param);
}

int main(int ac, char **av, char **env)
{
	t_global_info g_info;
	char *string;
	char *tmp;
	g_info.environ = dup_env(env);
	g_info.exit_code = 0;
	string = ft_strdup(" a   b    c ");
	printf("---------------  %s  -----------------\n", string);
	tmp = space_trim(string);
	printf("%s\n", tmp);
	// free(tmp);
}