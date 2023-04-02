/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:19:49 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/16 15:02:41 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	if (!(char)c)
		return ((char *)str + i);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i--;
	}
	return (0);
}

//#include<stdio.h>
//int main()
//{
//    char str[100] = "http://www.tutorialspoint.com";
//    char *ret;
//	ret = ft_strrchr(str,' ');
//    printf("%s",ret);
//    return (0);
//}