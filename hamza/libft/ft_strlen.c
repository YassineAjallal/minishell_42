/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:20:05 by hkasbaou          #+#    #+#             */
/*   Updated: 2023/05/11 19:24:31 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;
	if(!s)
		return 0;
	i = 0;
	while (s[i])
		i++;
	return (i);
}

//#include<stdio.h>
//int main(int argc, char const *argv[])
//{
//	char s[12]="hello nega";
//	printf("%zu", ft_strlen(s));
//	return (0);
//}
