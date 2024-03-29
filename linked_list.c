/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:37:24 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 11:18:00 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand	*add_new_node(char *value, int index, t_expand *head)
{
	t_expand	*new_node;
	t_expand	*nodes;

	nodes = head;
	new_node = (t_expand *)ft_malloc(sizeof(t_expand), 1);
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->index = index;
	new_node->next = NULL;
	if (!nodes)
		head = new_node;
	else
	{
		while (nodes->next)
			nodes = nodes->next;
		nodes->next = new_node;
	}
	return (head);
}

t_expand	*delete_node(t_expand *head, int index)
{
	t_expand	*node;
	t_expand	*remove;

	node = head;
	if (!head)
		return (NULL);
	if (head->index == index)
	{
		remove = head;
		head = head->next;
		return (head);
	}
	while (node->next)
	{
		if (node->next->index == index)
		{
			remove = node->next;
			node->next = node->next->next;
		}
		if (node->next)
			node = node->next;
	}
	return (head);
}

void	num_list(t_expand *head)
{
	t_expand	*node;
	int			i;

	node = head;
	i = 0;
	while (node)
	{
		node->index = i;
		i++;
		node = node->next;
	}
}

int	lst_size(t_expand *head)
{
	int			i;
	t_expand	*node;

	node = head;
	i = 0;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

t_expand	*delete_empty(t_expand *head)
{
	t_expand	*node;

	node = head;
	while (node)
	{
		if (ft_strlen(node->value) == 0)
			head = delete_node(head, node->index);
		node = node->next;
	}
	return (head);
}
