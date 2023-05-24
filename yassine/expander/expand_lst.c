/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:10:04 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/24 19:10:57 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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