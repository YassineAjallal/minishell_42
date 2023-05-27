/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:34:52 by yajallal          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/27 19:17:34 by yajallal         ###   ########.fr       */
=======
/*   Updated: 2023/05/26 19:48:07 by yajallal         ###   ########.fr       */
>>>>>>> 70e09aa5340cdf07290fe1e1d1aad6521db2032f
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_malloc
{
	void			*address;
	struct s_malloc	*next;
}	t_malloc;

void		*ft_malloc(size_t size, int mode);

t_malloc	*add_new_node_malloc(void *address, t_malloc *head);
t_malloc	*delete_addr(t_malloc *head);
<<<<<<< HEAD
=======
void *ft_malloc(size_t size, int mode);
>>>>>>> 70e09aa5340cdf07290fe1e1d1aad6521db2032f
#endif