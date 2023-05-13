/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:20:09 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/12 23:22:18 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
//#include<stdio.h>
//#include<string.h>
//int main(int argc, char const *argv[])
//{
//	char *dest;
//	memset(dest, 0, 15);
//	memset(dest, 'r', 6);
//    printf("%d: %s n",(int)ft_strlcpy(dest, "", 15), dest);

//    char s1[] = "Hello there, Venus";
//    char d1[20];
//    int i = ft_strlcpy(d1, s1, 4);
//    printf("%d: %s \t %s",i,s1,d1);
//    return (0);
//}