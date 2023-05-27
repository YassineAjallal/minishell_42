/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:34:52 by yajallal          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/26 19:48:07 by yajallal         ###   ########.fr       */
=======
/*   Updated: 2023/05/26 19:29:40 by yajallal         ###   ########.fr       */
>>>>>>> e5f8521e8c1ced501327ec9974d71c23fac40ee6
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

<<<<<<< HEAD
t_malloc	*add_new_node_malloc(void *address, t_malloc *head);
t_malloc	*delete_addr(t_malloc *head);
void *ft_malloc(size_t size, int mode);
=======
t_malloc	*add_new_node(void *address, t_malloc *head);
t_malloc	*delete_addr(t_malloc *head);
void print(t_malloc *head);
t_malloc *free_nodes(t_malloc *head);
>>>>>>> e5f8521e8c1ced501327ec9974d71c23fac40ee6
#endif