/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:20:25 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/12 23:22:02 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i++;
	}
	if (!(char)c)
		return ((char *)str + i);
	return (0);
}
//#include<stdio.h>
//int main()
//{
//	char str[] = "http://www.tutorialspoint.com";
//	char *ret = ft_strchr(str,'.');
//	printf("%s",ret);
//	return (0);
//}
