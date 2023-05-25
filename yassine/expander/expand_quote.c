/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:52:51 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/25 11:01:37 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_expand *init_node_quote(t_expand *node, t_expand *new_node, t_global_info *g_info)
{
	if (node->value[0] == '\"')
	{
		node->value = ft_strtrim(node->value, "\'\"");
		node->value = expand_var(node->value, g_info);
		new_node = add_new_node(node->value, node->index, new_node);
	}
	else
	{
		node->value = ft_strtrim(node->value, "\'\"");
		new_node = add_new_node(node->value, node->index, new_node);
	}
	num_list(new_node);
	return (new_node);
}

t_expand *expand_double_quote(t_expand *node, t_expand *new_node, t_global_info *g_info, char *prev)
{
	int len;

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
	return (new_node);
}

t_expand *expand_single_quote(t_expand *node, t_expand *new_node, char *prev)
{
	int len;

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
	return (new_node);
}

t_expand *expand_linked_quote(t_expand *node, t_expand *new_node, t_global_info *g_info, char *prev)
{
	if (node->value[0] == '\"')
		new_node = expand_double_quote(node, new_node, g_info, prev);
	else
		new_node = expand_single_quote(node, new_node, prev);
	num_list(new_node);
	return (new_node);
}
