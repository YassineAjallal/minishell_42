/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:20:17 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/28 20:11:51 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	ttl;
	char	*str;
	size_t	i;
	int		j;

	i =  -1;
	j = 0;
	ttl = ft_strlen(s2) + ft_strlen(s1);
	str = ft_calloc(ttl + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	return (str);
}

//#include<stdio.h>
//int main(int argc, char const *argv[])
//{
//	char s[] = "hello";
//    char ss[] ="bro cv";
//    char *str = ft_strjoin(s,ss);
//    printf("%s", str);
//	return (0);
//}
