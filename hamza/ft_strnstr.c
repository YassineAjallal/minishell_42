/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:19:54 by hkasbaou          #+#    #+#             */
/*   Updated: 2022/10/18 21:52:03 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	char	*s1;
	char	*s2;

	s1 = (char *)haystack;
	s2 = (char *)needle;
	if (!*s2)
		return (s1);
	if (!len)
		return (0);
	if (!*s1)
		return (0);
	while (len - ft_strlen(s2) + 1 > 0 && *s1)
	{
		j = 0;
		if (ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
			return (s1);
		len--;
		s1++;
	}
	return (NULL);
}
