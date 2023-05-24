/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/24 19:51:00 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_expand	*quote_expand(t_expand *head, char *string, char c, int *i)
{
	int		index;
	int		pos;
	char	*substr;

	index = *i;
	pos = index;
	index++;
	while (string[index] != c && string[index])
		index++;
	if (string[index] == c)
		index++;
	substr = ft_substr(string, pos, index - pos);
	*i = index;
	head = add_new_node(substr, 0, head);
	return (head);
}

t_expand	*ft_expand(char *string)
{
	t_expand	*head;
	char		*substr;
	int			pos;
	int			i;

	i = 0;
	head = NULL;
	while (string[i])
	{
		if (string[i] == '\"')
			head = quote_expand(head, string, '\"', &i);
		else if (string[i] == '\'')
			head = quote_expand(head, string, '\'', &i);
		else
		{
			pos = i;
			while (string[i] != '\"' && string[i] != '\'' && string[i])
				i++;
			substr = ft_substr(string, pos, i - pos);
			head = add_new_node(substr, 0, head);
		}
	}
	num_list(head);
	return (head);
}

char	**join_all_param(t_expand *head, char *param, t_global_info *g_info)
{
	char	**head_array;

	head = ft_expand(param);
	head = expand_linked_list(head, g_info);
	head = delete_empty(head);
	head_array = convert_linked_array(head);
	return (head_array);
}

char	**expand_all_param(t_command *cmd)
{
	int			i;
	char		**expanded_param;
	char		**head_array;
	t_expand	*head;

	head = NULL;
	i = 0;
	expanded_param = malloc(sizeof(char *));
	expanded_param[0] = NULL;
	while (cmd->cmd_parameter[i])
	{
		head_array = join_all_param(head, cmd->cmd_parameter[i], cmd->g_info);
		expanded_param = ft_strjoin2d(expanded_param, head_array);
		i++;
	}
	if (cmd->cmd)
	{
		if (ft_strlen(cmd->cmd) > 0)
			cmd->cmd = ft_strdup(expanded_param[0]);
		else if (cmd->cmd && ft_strlen(cmd->cmd) == 0)
			cmd->cmd = ft_strdup("");
		i = 0;
		cmd->cmd = to_lower(cmd->cmd);
	}
	return (expanded_param);
}
