/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 00:28:19 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 13:20:15 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_command.h"

int	ft_strlen2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*multiple_join(char **path, int length)
{
	int		i;
	char	*tmp;
	char	*new_path;
	char	*add_slash;

	i = 1;
	new_path = ft_strdup("");
	new_path = ft_strjoin(new_path, path[0]);
	while (i < length)
	{
		add_slash = ft_strjoin("/", path[i]);
		tmp = ft_strjoin(new_path, add_slash);
		new_path = tmp;
		i++;
	}
	return (new_path);
}

void	ft_free2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return;
	while (str[i])
		free(str[i++]);
	if (str)
		free(str);
	str = NULL;
}

void	*env_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = (void *)malloc(count * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}

char	*env_substr(char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			length;

	i = 0;
	length = ft_strlen(s);
	if (start >= length)
		return (env_calloc(sizeof(char), 1));
	if (len >= length)
		len = length - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*env_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + 1);
	if (!str)
		return (NULL);
	while ((unsigned char)s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*env_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	j = 0;
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}