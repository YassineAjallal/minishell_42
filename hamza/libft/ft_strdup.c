/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:20:21 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/16 20:41:50 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s;

	s = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

//#include<stdio.h>
//int main(int argc, char const *argv[])
//{
//	char *s = ft_strdup("hellocv");
//	printf("%s",s);
//	return 0;
//}
