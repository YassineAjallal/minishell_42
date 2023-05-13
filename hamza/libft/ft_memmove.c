/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:17:28 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/21 00:16:07 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;
	size_t	i;

	i = -1;
	d = (char *)dst;
	s = (char *)src;
	if (!d && !s)
		return (NULL);
	if (d > s)
	{
		while (len > 0)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	else
	{
		while (++i < len)
			d[i] = s[i];
	}
	return (d);
}

//#include<stdio.h>
//#include<string.h>
//int main(int argc, char const *argv[])
//{
//	char s[] = "helloworld";
//	ft_memmove(s+5, s, 5);
//	printf("%s",s);
//}
