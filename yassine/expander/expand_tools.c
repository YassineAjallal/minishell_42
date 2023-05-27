/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:11:07 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 11:15:05 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	**convert_linked_array(t_expand *head)
{
	char		**array_conv;
	t_expand	*node;
	int			i;

	array_conv = ft_malloc(sizeof(char *) * (lst_size(head) + 1), 1);
	node = head;
	i = 0;
	if (!array_conv)
		return (NULL);
	while (node)
	{
		array_conv[i] = ft_strdup(node->value);
		i++;
		node = node->next;
	}
	array_conv[i] = NULL;
	return (array_conv);
}

char	**ft_strjoin2d(char **s1, char **s2)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = ft_malloc(sizeof(char *) * (ft_strlen2d(s1) + ft_strlen2d(s2) + 1), 1);
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = ft_strdup(s1[i]);
		i++;
	}
	while (s2[j])
	{
		new[i] = ft_strdup(s2[j]);
		i++;
		j++;
	}
	new[i] = NULL;
	return (new);
}

int	search_in_env(t_env *env, char *string)
{
	int	i;

	i = 0;
	while (i < env->nb_variables)
	{
		if (ft_strcmp(string, env->variables[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*to_lower(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		command[i] = ft_tolower(command[i]);
		i++;
	}
	return (command);
}
