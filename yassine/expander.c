/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/09 11:55:37 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_expand {
	char *string;
	bool is_expand;
	
} t_expand;

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

char *expand_var(char *string, t_env *env)
{
	int i;
	int index_var;
	char *expanded_string;
	char *var_to_search;
	int next_pos;
	char *tmp;

	i = 0;
	while (string[i] != '$' && string[i])
		i++;
	expanded_string = ft_substr(string, 0, i);
	while (string[i])
	{
		if (string[i] == '$')
		{
			i++;
			next_pos = next_dollar_pos(string, i);
			if (var_to_search)
				free(var_to_search);
			var_to_search = ft_substr(string, i, next_pos - i);
			index_var = search_in_env(env, var_to_search);
			if (index_var > -1)
			{
				tmp = ft_strjoin(expanded_string, env->variables[index_var].value);
				free(expanded_string);
				expanded_string = tmp;
			}
			i = next_pos;
		}
		else
			i++;
	}
	free(string);
	if (var_to_search)
			free(var_to_search);
	return (expanded_string);
}

char *ft_expand(char *string, t_env *env)
{
	char *string_expand;
	char *tmp;
	if (string[0] != '\'')
	{
		tmp = ft_strtrim(string, "\"");
		free(string);
		string_expand = expand_var(tmp, env);
	}
	else
	{
		string_expand = ft_strtrim(string, "\'");
		free(string);
	}
	return (string_expand);
}

int main(int ac, char **av, char **env)
{
	t_env *environ;
	char *string;
	char *tmp;
	environ = dup_env(env);
	string = ft_strdup("\"hello$HOME$USER$PWD\"");
	printf("---------------  %s  -----------------\n\n\n", string);
	tmp = ft_expand(string, environ);
	printf("%s\n", tmp);
	free(tmp);
}