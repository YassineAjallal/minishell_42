/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:59:49 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/12 23:22:23 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	int		i;

	i = 0;
	p = ft_calloc(ft_strlen(s) + 1, 1);
	if (!p)
		return (NULL);
	while (s[i])
	{
		p[i] = f(i, s[i]);
		i++;
	}
	return (p);
}
//#include<stdio.h>
//int main(int argc, char const *argv[])
//{
//    char s[] = "hello cc";
//    ft_strmapi(s, str);
//    printf("%s",s);
//    return (0);
//}
