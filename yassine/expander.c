/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/16 19:37:24 by yajallal         ###   ########.fr       */
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

char *space_trim(char *str, char c)
{
	int i;
	char **split_space;
	char *string_trim;
	char *tmp;

	i = 0;
	string_trim = malloc(sizeof(char));
	string_trim[0] = 0;
	if (!str)
		return (NULL);
	split_space = ft_split(str, c);
	while(split_space[i])
	{
		string_trim = ft_strjoin(string_trim, split_space[i]);
		i++;
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
		{
			// char *tmp1;
			// tmp1 = space_trim(g_info->environ->variables[var_index].value);
			// g_info->environ->variables[var_index].value = tmp1;
			tmp = ft_strjoin(expand_string, g_info->environ->variables[var_index].value);
		}
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
		expand_string = ft_strjoin(expand_string, "$");
	}
	return (expand_string);
}

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
	while(s1[i])
	{
		new_array[i] = ft_strdup(s1[i]);
		i++;
	}
	while(s2[j])
	{
		new_array[i] = ft_strdup(s2[j]);
		i++;
		j++;
	}
	new_array[i] = NULL;
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
	return (new_array);
}


char *ft_expand(char *string, t_global_info *g_info)
{
	int i;
	int j;
	char *expand;
	char **new_cmd_param;
	char *tmp;
	char *expand_without_q;
	char **quote;
	char *expand_double_q;
	int last_el;
	int pos;

	i = 0;
	new_cmd_param = malloc(sizeof(char *));
	if (!new_cmd_param)
		return (NULL);
	new_cmd_param[0] = NULL;
	expand= malloc(sizeof(char));
	expand[0] = 0;
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
			expand = ft_strjoin(expand, "\"");
			// printf("expand %s\n", expand);
			expand = ft_strjoin(expand, expand_double_q);
			expand = ft_strjoin(expand, "\"");
			// new_cmd_param[ft_strlen2d(new_cmd_param) - 1] = ft_strjoin(new_cmd_param[ft_strlen2d(new_cmd_param) - 1], expand_double_q);
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
			// new_cmd_param[ft_strlen2d(new_cmd_param) - 1] = ft_strjoin(new_cmd_param[ft_strlen2d(new_cmd_param) - 1], expand_double_q);
			expand = ft_strjoin(expand, "\'");
			expand = ft_strjoin(expand, expand_double_q);
			expand = ft_strjoin(expand, "\'");
		}
		else
		{
			pos = i;
			while(string[i] != '\"' && string[i] != '\'' && string[i])
				i++;
			tmp = ft_substr(string, pos, i);
			expand_without_q = expand_var(tmp, g_info);
			// char **expand_without_q_2d;
			// expand_without_q_2d = ft_split(expand_without_q, ' ');
			expand = ft_strjoin(expand, expand_without_q);
			// if (ft_strlen2d(expand_without_q_2d) == 0)
			// {
			// 	expand_without_q_2d = strjoin2d_string(expand_without_q_2d, " ");
			// }	
			// last_el = ft_strlen2d(new_cmd_param);
			// if (last_el > 0)
			// {
			// 	if (expand_without_q[0] != ' ' && new_cmd_param[last_el - 1][ft_strlen(new_cmd_param[last_el - 1]) - 1] != ' ')
			// 	{
			// 		new_cmd_param[ft_strlen2d(new_cmd_param) - 1] = ft_strjoin(new_cmd_param[ft_strlen2d(new_cmd_param) - 1], expand_without_q);
			// 	}
			// 	else
			// 	{
			// 		new_cmd_param = ft_strjoin2d(new_cmd_param, expand_without_q_2d);
			// 	}
			// }
			// else
			// {
			// 	new_cmd_param = ft_strjoin2d(new_cmd_param, expand_without_q_2d);
			// }
		}
	}
	// printf("-------%s-------\n", expand);
	return (expand);
}

int split_expander_len(char *expand_all)
{
	int i;
	int count;
	char c;
	i = 0;
	count = 0;
	while (expand_all[i] == ' ')
		i++;
	while(expand_all[i])
	{
		if (expand_all[i] == '\"')
		{
			i++;
			while(expand_all[i] != '\"' && expand_all[i])
				i++;
			count++;
			i++;
		}
		else if (expand_all[i] == '\'')
		{
			i++;
			while(expand_all[i] != '\'' && expand_all[i])
				i++;
			count++;
			i++;
		}
		else
		{
			while(expand_all[i] != ' ' && expand_all[i])
			{
				if (expand_all[i] == '\"' || expand_all[i] == '\'')
				{
					c = expand_all[i];
					i++;
					while (expand_all[i] != c)
						i++;
				}
				i++;
			}
			count++;
		}
		while (expand_all[i] == ' ')
			i++;
	}
	return(count);
}


int	ft_len(char *s, char c, int p)
{
	int	len;
	char save;

	len = 0;
	
	if (c == ' ')
	{
		while (s[p] != c && s[p] != '\0')
		{
			if (s[p] == '\"' || s[p] == '\'')
			{
				save = s[p];
				len++;
				p++;
				while (s[p] != save)
				{
					len++;
					p++;
				}
			}
			len++;
			p++;
		}
	}
	else
	{
		while (s[p] != c && s[p] != '\0')
		{
			len++;
			p++;
		}
	}
	return (len);
}


char **split_expander(char *expand_all)
{
	int nb_word;
	char **split_exp;
	int len;
	int j;
	int i;
	
	i = 0;
	j = 0;
	nb_word = split_expander_len(expand_all);
	split_exp = malloc(sizeof(char *) * (nb_word + 1));
	if (!split_exp)
		return (NULL);
	while(expand_all[i] == ' ')
		i++;
	while(expand_all[i])
	{
		while(expand_all[i] == ' ')
			i++;
		if (expand_all[i])
		{	
			if (expand_all[i] == '\"')
			{
				i++;
				len = ft_len(expand_all, '\"', i);
				split_exp[j] = ft_substr(expand_all, i, len);
				j++;
				while(expand_all[i] != '\"' && expand_all[i])
					i++;
			}
			else if (expand_all[i] == '\'')
			{
				i++;
				len = ft_len(expand_all, '\'', i);
				split_exp[j] = ft_substr(expand_all, i, len);
				j++;
				while(expand_all[i] != '\'' && expand_all[i])
					i++;
			}
			else
			{
				len = ft_len(expand_all, ' ', i);
				split_exp[j] = ft_substr(expand_all, i, len);
				j++;
				// while(expand_all[i] != ' ' && expand_all[i])
				// 	i++;
				i += len;
			}
			i++;
		}
	}
	split_exp[j] = NULL;
	return(split_exp);
}

char **expand_all_param(t_command *cmd, t_global_info *g_info)
{
	int i;
	char **expanded_param;
	char *expand_all;
	char *exp;

	i = 0;
	expand_all = malloc(sizeof(char));
	expand_all[0] = 0;
	while(cmd->cmd_parameter[i])
	{
		exp = ft_expand(cmd->cmd_parameter[i], g_info);
		exp = ft_strjoin(exp, " ");
		expand_all = ft_strjoin(expand_all, exp);
		i++;
	}
	expanded_param = split_expander(expand_all);
	i = 0;
	while (expanded_param[i])
	{
		expanded_param[i] = space_trim(expanded_param[i], '\"');
		expanded_param[i] = space_trim(expanded_param[i], '\'');
		i++;
	}	
	cmd->cmd = ft_strdup(expanded_param[0]);
	ft_free2d(cmd->cmd_parameter);
	return(expanded_param);
}

// int main(int ac, char **av, char **env)
// {
// 	t_global_info g_info;
// 	char *string;
// 	char *tmp;
// 	g_info.environ = dup_env(env);
// 	g_info.exit_code = 0;
// 	string = ft_strdup(" a   b    c ");
// 	printf("---------------  %s  -----------------\n", string);
// 	tmp = space_trim(string);
// 	printf("%s\n", tmp);
// 	// free(tmp);
// }