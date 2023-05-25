/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_no_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:48:27 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/25 11:07:05 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_expand *init_node_no_quote(t_expand *node, t_expand *new_node)
{
	char **split;
	int i;

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
	}
	num_list(new_node);
	return (new_node);
}
t_expand *expand_with_space(t_expand *node, t_expand *new_node, char **split, char *prev_q)
{
	t_expand *node_splited;
	int i;

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
	return (new_node);
}

t_expand *expand_linked_no_quote(t_expand *node, t_expand *new_node, char *prev_q)
{
	char **split;

	split = ft_split(node->value, ' ');
	if (ft_strlen2d(split) > 0)
		new_node = expand_with_space(node, new_node, split, prev_q);
	else
	{
		if (ft_strlen(node->value) > 0)
			new_node = add_new_node(ft_strdup(""), 0, new_node);
	}
	num_list(new_node);
	return (new_node);
}
