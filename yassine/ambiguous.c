/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:38:13 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/24 10:57:11 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ambiguous_checker(char *file, t_global_info *g_info)
{
	int	len;

	if (ft_strchr(file, '$'))
	{
		file = expand_var(file, g_info);
		len = ft_strlen(file);
		if (file[0] == '\"' && file[len - 1] == '\"' && len == 2)
		{
			g_info->exit_code = 0;
			return (1);
		}
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		g_info->exit_code = 1;
		return (0);
	}
	g_info->exit_code = 0;
	return (1);
}

char	*ambiguous_redirect(char *file, t_global_info *g_info)
{
	char		**head_array;
	t_expand	*head;

	head = ft_expand(file);
	head = expand_linked_list(head, g_info);
	head = delete_empty(head);
	head_array = convert_linked_array(head);
	if (ft_strlen2d(head_array) == 0)
	{
		if (ambiguous_checker(file, g_info))
			return (ft_strdup(""));
		else
			return (NULL);
	}
	else if (ft_strlen2d(head_array) > 1)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		g_info->exit_code = 1;
		return (NULL);
	}
	g_info->exit_code = 0;
	return (head_array[0]);
}
