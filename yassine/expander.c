/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/22 19:56:23 by yajallal         ###   ########.fr       */
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


t_expand *ft_expand(char *string)
{
	t_expand *head;
	char *substr;
	int j;
	int pos;
	int i;

	i = 0;
	j = 0;
	head = NULL;
	while(string[i])
	{
		if (string[i] == '\"')
		{
			pos = i;
			i++;
			while(string[i] != '\"' && string[i])
				i++;
			if (string[i] == '\"')
				i++;
			substr = ft_substr(string, pos, i - pos);
			head = add_new_node(substr, j, head);
			j++;
		}
		else if (string[i] == '\'')
		{
			pos = i;
			i++;
			while(string[i] != '\'' && string[i])
				i++;
			if (string[i] == '\'')
				i++;
			substr = ft_substr(string, pos, i - pos);
			head = add_new_node(substr, j, head);
			j++;
		}
		else
		{
			pos = i;
			while(string[i] != '\"' && string[i] != '\'' && string[i])
				i++;
			substr = ft_substr(string, pos, i - pos);
			head = add_new_node(substr, j, head);
			j++;
		}
	}
	return (head);
}

void print(t_expand *head)
{
	t_expand *node;

	node = head;
	while(node)
	{
		printf("%d : --%s--\n", node->index, node->value);
		node = node->next;
	}
}

void num_list(t_expand *head)
{
	t_expand *node;
	int i;

	node = head;
	i = 0;
	while(node)
	{
		node->index = i;
		i++;
		node = node->next;
	}
}
// void trim_list(t_expand *head)
// {
// 	t_expand *node;

// 	node = head;
// 	while(node)
// 	{
// 		node->value = ft_strtrim(node->value, "\'");
// 		node = node->next;
// 	}
// }

t_expand *expand_linked_list(t_expand *head, t_global_info *g_info)
{
	t_expand *new_node;
	t_expand *new_node_head;
	t_expand *node;
	t_expand *node_splited;
	char *prev;
	char *prev_q;
	char **split;
	int i;
	int len;
	
	node = head;
	new_node = NULL;
	new_node_head = new_node;
	node_splited = NULL;
	prev = ft_strdup("");
	if (node->value[0] == '\'' || node->value[0] == '\"')
	{
		if (node->value[0] == '\"')
		{
			node->value = ft_strtrim(node->value, "\'\"");
			node->value = expand_var(node->value, g_info);
			new_node = add_new_node(node->value, node->index, new_node);
			new_node_head = new_node;
		}
		else
		{
			node->value = ft_strtrim(node->value, "\'\"");
			new_node = add_new_node(node->value, node->index, new_node);
			new_node_head = new_node;
		}
		num_list(new_node);
	}
	else
	{
		node->value = expand_var(node->value, g_info);
		prev = ft_strdup(node->value);
		split = ft_split(node->value, ' ');
		i = 0;
		if (ft_strlen2d(split) > 0)
		{
			while(split[i])
			{
				new_node = add_new_node(split[i], i, new_node);
				i++;
			}
		}
		else
		{
			new_node = add_new_node(ft_strdup(""), 0, new_node);
			num_list(new_node);
		}
		new_node_head = new_node;
	}
	
	node = node->next;
	while(node)
	{
		if (node->value[0] == '\'' || node->value[0] == '\"')
		{
			if (node->value[0] == '\"')
			{
				node->value = ft_strtrim(node->value, "\'\"");
				node->value = expand_var(node->value, g_info);
				while(new_node->next)
						new_node = new_node->next;
				len = ft_strlen(prev);
				if (len > 0)
				{
					if (prev[len - 1] == ' ' || prev[len - 1] == '\t')
						new_node = add_new_node(node->value, node->index, new_node);
					else
						new_node->value = ft_strjoin(new_node->value, node->value);
				}
				else
					new_node->value = ft_strjoin(new_node->value, node->value);
				prev_q = ft_strdup("");
			}
			else
			{
				node->value = ft_strtrim(node->value, "\'\"");
				while(new_node->next)
						new_node = new_node->next;
				len = ft_strlen(prev);
				if (len > 0)
				{
					if (prev[len - 1] == ' ' || prev[len - 1] == '\t')
						new_node = add_new_node(node->value, node->index, new_node);
					else
						new_node->value = ft_strjoin(new_node->value, node->value);
				}
				else
					new_node->value = ft_strjoin(new_node->value, node->value);
				prev_q = ft_strdup("");
			}
			num_list(new_node);
		}
		else
		{
			node->value = expand_var(node->value, g_info);
			prev = ft_strdup(node->value);
			split = ft_split(node->value, ' ');
			if (ft_strlen2d(split) > 0)
			{
				node_splited = NULL;
				i = 0;
				while(split[i])
				{
					node_splited = add_new_node(split[i], i, node_splited);
					i++;
				}
				while(new_node->next)
					new_node = new_node->next;
				if (prev_q[0] != ' ' && prev_q[0] != '\t'
					&& node->value[0] != ' ' && node->value[0] != '\t')
				{
					new_node->value = ft_strjoin(new_node->value, node_splited->value);
					node_splited = delete_node(node_splited, node_splited->index);
				}
				while(node_splited)
				{
					new_node = add_new_node(node_splited->value, node_splited->index, new_node);
					node_splited = node_splited->next;
				}
				num_list(new_node);
			}
			else
			{
				if (ft_strlen(node->value) > 0)
					new_node = add_new_node(ft_strdup(""), 0, new_node);
				num_list(new_node);
			}
		}
		node = node->next;
	}
	num_list(new_node_head);
	return (new_node_head);
}

int lst_size(t_expand *head)
{
	int i;
	t_expand *node;

	node = head;
	i = 0;
	while(node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

t_expand *delete_empty(t_expand *head)
{
	t_expand *node;

	node = head;
	while(node)
	{
		if (ft_strlen(node->value) == 0)
			head = delete_node(head, node->index);
		node = node->next;
	}
	return (head);
}

char **convert_linked_array(t_expand *head)
{
	char **array_conv;
	t_expand *node;
	int i;

	array_conv = malloc(sizeof(char *) * (lst_size(head) + 1));
	node = head;
	i = 0;
	if (!array_conv)
		return (NULL);
	while(node)
	{
		array_conv[i] = ft_strdup(node->value);
		i++;
		node = node->next;
	}
	array_conv[i] = NULL;
	return (array_conv);
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

char **expand_all_param(t_command *cmd, t_global_info *g_info)
{
	int i;
	char **expanded_param;
	char **head_array;
	t_expand *head;

	head = NULL;
	i = 0;
	expanded_param = malloc(sizeof(char *));
	expanded_param[0] = NULL;
	while(cmd->cmd_parameter[i])
	{
		head = ft_expand(cmd->cmd_parameter[i]);
		head = expand_linked_list(head, g_info);
		head = delete_empty(head);
		head_array = convert_linked_array(head);
		expanded_param = ft_strjoin2d(expanded_param, head_array);
		i++;
	}
	if (cmd->cmd)
	{
		if (ft_strlen(cmd->cmd) > 0)
			cmd->cmd = ft_strdup(expanded_param[0]);
		else if (!cmd->cmd)
			cmd->cmd = NULL;
		else
			cmd->cmd = ft_strdup("");
		i = 0;
		while(cmd->cmd[i])
		{
			cmd->cmd[i] = ft_tolower(cmd->cmd[i]);
			i++;
		}
		// printf("cmd : --%s--\n", cmd->cmd);
	}
	return(expanded_param);
}

// int main(int ac, char **av, char **env)
// {
// 	t_global_info g_info;
// 	char *string;
// 	char *tmp;
// 	g_info.environ = dup_env(env);
// 	g_info.exit_code = 0;
// 	string = ft_strdup("\"foobar\"$a\"bar\"");
// 	printf("---------------  %s  -----------------\n", string);
// 	t_expand *head;
// 	t_expand *node;

// 	head = NULL;
// 	head = ft_expand(string);
// 	print(head);
// 	head = expand_linked_list(head, &g_info);
// 	print(head);
// 	// head = delete_node(head, 1);
// 	// head = delete_node(head, 0);
// 	// head = delete_node(head, 3);
// 	// node = head;
// 	// while(node)
// 	// {
// 	// 	printf("%d : --%s--\n", node->index, node->value);
// 	// 	node = node->next;
// 	// }
	
// 	// free(tmp);
// }