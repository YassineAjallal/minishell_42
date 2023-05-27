/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:09:14 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/26 19:56:22 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void *ft_malloc(size_t size, int mode)
{
	static t_malloc *list_address;
	void *address;
	if (mode == 1)
	{
		address = malloc(size);
		if (!address)
			return (NULL);
		list_address = add_new_node_malloc(address, list_address);
		return (address);
	}
	else if (mode == 0)
		list_address = delete_addr(list_address);
	return (NULL);
}