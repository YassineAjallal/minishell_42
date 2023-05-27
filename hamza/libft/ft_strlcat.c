/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:20:12 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/11/01 20:24:39 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;

	i = 0;
	lensrc = ft_strlen(src);
	if (size == 0)
		return (lensrc);
	lendst = ft_strlen(dst);
	if (size <= lendst)
		return (lensrc + size);
	else
	{
		i = lendst;
		while (*src && i < size - 1)
		{
			dst[i++] = *(src++);
		}
		dst[i] = 0;
		return (lensrc + lendst);
	}
}

#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	dst[] = "hello world dshdjshdjsdh shdjhsdjhsjdh";
	char	src[] = "wo";
	
	printf("%ld\n", ft_strlcat(dst, src, 3));
	printf("%s\n", dst);
}
