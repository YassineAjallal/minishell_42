/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:21:49 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/15 20:24:49 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	space(char str)
{
	if (str == ' ' || str == '\r' || str == '\f' || str == '\v' || str == '\n'
		|| str == '\t')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	rsl;

	rsl = 0;
	i = 0;
	sign = 1;
	while (space(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rsl = str[i] + (rsl * 10) - '0';
		i++;
	}
	return (rsl * sign);
}

//#include<stdio.h>
//int main(int argc, char const *argv[])
//{
//	printf("%d\n", atoi("+548"));
//	printf("%d",ft_atoi("+548"));
//	return (0);
//}
