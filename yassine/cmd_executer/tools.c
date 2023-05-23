/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:20:09 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/23 15:48:35 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_executer.h"

char	*quote_trim(char *str, char c)
{
	int		i;
	char	**split_quote;
	char	*string_trim;

	i = 0;
	string_trim = malloc(sizeof(char));
	string_trim[0] = 0;
	if (!str)
		return (NULL);
	split_quote = ft_split(str, c);
	while (split_quote[i])
	{
		string_trim = ft_strjoin(string_trim, split_quote[i]);
		i++;
	}
	return (string_trim);
}

int	search_heredoc(t_file **file, int i)
{
	while (file[i])
	{
		if (file[i]->mode == false)
			return (1);
		i++;
	}
	return (0);
}
