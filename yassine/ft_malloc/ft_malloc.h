/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:34:52 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/26 19:48:07 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include <stdlib.h>
#include <stdio.h>
typedef struct s_malloc
{
	void *address;
	struct s_malloc *next;
} t_malloc;

t_malloc	*add_new_node_malloc(void *address, t_malloc *head);
t_malloc	*delete_addr(t_malloc *head);
void *ft_malloc(size_t size, int mode);
#endif