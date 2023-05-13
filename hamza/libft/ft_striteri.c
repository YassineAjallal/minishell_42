/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:26:07 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/23 16:08:43 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

//#include<stdio.h>
//int main(int argc, char const *argv[])
//{
//	char s[] = "abcde";
//	ft_striteri(s,f);
//	printf("%s",s);
//	return 0;
//}
