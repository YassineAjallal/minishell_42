/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal < yajallal@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:22:22 by yajallal          #+#    #+#             */
/*   Updated: 2023/01/13 12:24:57 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_free2d(char **str, char *s)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	free(s);
	str = NULL;
}

void	ft_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
}
