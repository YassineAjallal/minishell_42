/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:10:04 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 19:14:37 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_expand	*init_node(t_expand *node, t_expand *new_node, \
t_global_info *g_info, char **prev)
{
	if (node->value[0] == '\'' || node->value[0] == '\"')
		new_node = init_node_quote(node, new_node, g_info);
	else
	{
		node->value = expand_var(node->value, g_info);
		*prev = ft_strdup(node->value);
		new_node = init_node_no_quote(node, new_node);
	}
	return (new_node);
}

t_expand	*expand_nodes(t_expand *node, t_expand *new_node, \
t_global_info *g_info, char *prev)
{
	char	*prev_q;

	while (node)
	{
		if (node->value[0] == '\'' || node->value[0] == '\"')
		{
			new_node = expand_linked_quote(node, new_node, g_info, prev);
			prev_q = ft_strdup("");
			num_list(new_node);
		}
		else
		{
			node->value = expand_var(node->value, g_info);
			prev = ft_strdup(node->value);
			new_node = expand_linked_no_quote(node, new_node, prev_q);
		}
		node = node->next;
	}
	return (new_node);
}

t_expand	*expand_linked_list(t_expand *head, t_global_info *g_info)
{
	t_expand	*new_node;
	t_expand	*new_node_head;
	t_expand	*node;
	char		*prev;

	node = head;
	new_node = NULL;
	new_node_head = new_node;
	prev = ft_strdup("");
	new_node = init_node(node, new_node, g_info, &prev);
	new_node_head = new_node;
	node = node->next;
	new_node = expand_nodes(node, new_node, g_info, prev);
	num_list(new_node_head);
	return (new_node_head);
}
