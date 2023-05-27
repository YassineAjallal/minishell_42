/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:37:13 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/22 16:04:56 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cntnmb(long n)
{
	int	cnt;

	cnt = 0;
	if (n < 0)
		n *= (-1);
	while (n > 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

static char	*ifcheck(int cnt, long n)
{
	char	*t;

	if (n == 0)
	{
		t = ft_calloc(2, sizeof(char));
		if (!t)
			return (NULL);
		t[0] = '0';
	}
	if (n < 0)
	{
		t = ft_calloc((cnt + 2), sizeof(char));
		if (!t)
			return (NULL);
		t[0] = '-';
	}
	else if (n > 0)
	{
		t = ft_calloc((cnt + 1), sizeof(char));
		if (!t)
			return (NULL);
	}
	if (!t)
		return (NULL);
	return (t);
}

static char	*fill(char *tab, int cnt, long nb)
{
	if (nb < 0)
	{
		nb *= -1;
		while (cnt > 0)
		{
			tab[cnt--] = nb % 10 + '0';
			nb /= 10;
		}
	}
	else if (nb > 0)
	{
		cnt--;
		while (cnt >= 0)
		{
			tab[cnt--] = nb % 10 + '0';
			nb /= 10;
		}
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	char	*tab;
	long	nb;
	int		cnt;

	nb = n;
	cnt = cntnmb(nb);
	tab = ifcheck(cnt, n);
	if (!tab)
		return (NULL);
	tab = fill(tab, cnt, nb);
	return (tab);
}
