/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:37:24 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/19 16:35:36 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand *add_new_node(char *value, int index, t_expand *head)
{
	t_expand *new_node;
	t_expand *nodes;

	nodes = head;
	new_node = (t_expand *)malloc(sizeof(t_expand));
	if (!new_node)
		return (NULL);

	new_node->value = value;
	new_node->index = index;
	new_node->next = NULL;
	if (!nodes)
		head = new_node;
	else
	{
		while(nodes->next)
			nodes = nodes->next;
		nodes->next = new_node;
	}
	return (head);
}

t_expand *delete_node(t_expand *head, int index)
{
	t_expand *node;
	t_expand *remove;

	node = head;
	remove = NULL;
	if (!head)
		return (NULL);
	if (head->index == index)
	{
		remove = head;
		head = head->next;
		free(remove);
		return (head);
	}
	while(node->next)
	{
		if (node->next->index == index)
		{
			remove  = node->next;
			node->next = node->next->next;
			free(remove);
		}
		if (node->next)
			node = node->next;
	}
	return (head);
}