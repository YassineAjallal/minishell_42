/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkasbaou <hkasbaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:16:01 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/28 16:52:02 by hkasbaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

char	*ft_strjoin_char(char const *s1, char s2)
{
	size_t	ttl;
	char	*str;
	size_t	i;
	int		j;

	i = -1;
	j = 0;
	ttl = ft_strlen(&s2) + ft_strlen(s1);
	str = ft_calloc(ttl + 1, sizeof(char));
	if (!str || !s2)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	str[i++] = s2;
	str[i++] = '\0';
	return (str);
}

char	**ft_strjoin_2d(char **s1, char *s2)
{
	int		i;
	int		j;
	char	**new_array;

	i = 0;
	j = 0;
	new_array = ft_malloc(sizeof(char *) * (ft_strlen2d(s1) + 2),1);
	if (!new_array)
		return (NULL);
	while (s1[i] && s1)
	{
		new_array[i] = ft_strdup(s1[i]);
		i++;
	}
	new_array[i] = ft_strdup(s2);
	i++;
	new_array[i] = NULL;
	return (new_array);
}

int	ft_strlen_out(t_file **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_file	**ft_strjoin_in(t_file **s1, char *s2, char *mode)
{
	int		i;
	int		j;
	t_file	**new_array;

	i = 0;
	j = 0;
	new_array = ft_malloc(sizeof(t_file *) * (ft_strlen_out(s1) + 2),1);
	if (!new_array)
		return (NULL);
	while (s1[i] && s1)
	{
		new_array[i] = ft_malloc(1 * sizeof(t_file),1);
		new_array[i]->file = s1[i]->file;
		new_array[i]->mode = s1[i]->mode;
		i++;
	}
	new_array[i] = ft_malloc(1 * sizeof(t_file),1);
	new_array[i]->file = s2;
	if ((mode[0] == '<' && mode[1] == '<'))
		new_array[i]->mode = false;
	else if (mode[0] == '<')
		new_array[i]->mode = true;
	i++;
	new_array[i] = NULL;
	return (new_array);
}

t_file	**ft_strjoin_out(t_file **s1, char *s2, char *mode)
{
	int		i;
	int		j;
	t_file	**new_array;

	i = 0;
	j = 0;
	new_array = ft_malloc(sizeof(t_file *) * (ft_strlen_out(s1) + 2),1);
	if (!new_array)
		return (NULL);
	while (s1[i] && s1)
	{
		new_array[i] = ft_malloc(1 * sizeof(t_file),1);
		new_array[i]->file = s1[i]->file;
		new_array[i]->mode = s1[i]->mode;
		i++;
	}
	new_array[i] = ft_malloc(1 * sizeof(t_file),1);
	new_array[i]->file = s2;
	if ((mode[0] == '>' && mode[1] == '>'))
		new_array[i]->mode = false;
	else if (mode[0] == '>')
		new_array[i]->mode = true;
	i++;
	new_array[i] = NULL;
	return (new_array);
}



