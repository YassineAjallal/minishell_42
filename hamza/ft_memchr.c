/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:20:57 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/16 20:23:01 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)str == (unsigned char)c)
			return ((void *)str);
		str++;
	}
	return (NULL);
}

//#include<stdio.h>
//int main()
//{
//	char str[] = "http://www.tutorialspoint.com";
//	char *ret = ft_memchr(str,'.',ft_strlen(str));
//	printf("%s",ret);
//	return (0);
//}