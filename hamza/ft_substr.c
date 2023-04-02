/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:19:40 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/15 13:36:51 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*str;
	int		siz;

	siz = start;
	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return ((char *)ft_calloc(1, sizeof(char)));
	if (ft_strlen(s) <= start + len)
		str = ft_calloc(sizeof(char), (ft_strlen(s) - start + 1));
	else
		str = ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (NULL);
	while (s[start] && start < len + siz)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	return (str);
}
