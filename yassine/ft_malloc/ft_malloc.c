/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 19:09:14 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/26 19:39:15 by yajallal         ###   ########.fr       */
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
		list_address = add_new_node(address, list_address);
		return (address);
	}
	else if (mode == 0)
		list_address = delete_addr(list_address);
	return (NULL);
}

// int main()
// {
// 	char *ptr, *ptr1, *ptr2, *ptr3;
	
// 	ptr2 = ft_malloc(sizeof(char), 1);
// 	ptr3 = ft_malloc(sizeof(char), 1);
// 	ptr2 = ptr3;
// 	ptr1 = ft_malloc(sizeof(char), 1);
// 	ptr = ft_malloc(sizeof(char), 1);
// 	ft_malloc(0, 0);
// 	ft_malloc(0, 0);
// 	ptr = ptr1;
// 	if (!ptr)
// 		return 0;
// }