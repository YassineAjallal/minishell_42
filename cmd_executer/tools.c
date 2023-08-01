/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:20:09 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/30 11:48:45 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_executer.h"

char	*quote_trim(char *str, char c)
{
	int		i;
	char	**split_quote;
	char	*string_trim;

	i = 0;
	string_trim = ft_malloc(sizeof(char), 1);
	if (!string_trim)
		return (NULL);
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

void	handler_herdoc(int signal)
{
	(void)signal;
	exit(1);
}

void	herdoc_process(t_file *infile, int is_expanded, \
int heredoc_pipe[2], t_global_info *g_info)
{
	char	*tmp;
	char	*heredoc_input;

	while (1)
	{
		signal(SIGINT, handler_herdoc);
		heredoc_input = readline("> ");
		tmp = heredoc_input;
		if (!heredoc_input)
			exit(0);
		else if (!ft_strcmp(infile->file, heredoc_input))
		{
			free(tmp);
			exit(0);
		}
		else
		{
			if (is_expanded == 1)
				heredoc_input = expand_var(heredoc_input, g_info);
			write(heredoc_pipe[1], heredoc_input, ft_strlen(heredoc_input));
			write(heredoc_pipe[1], "\n", 1);
			free(tmp);
		}
	}
}
