/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:08:23 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/25 17:41:13 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "herdoc.h"

// int check_delimiter(char *line, char *delimiter)
// {
// 	char **split_line;

// 	split_line = ft_split(line, ' ');
// 	if (!split_line)
// 		return (0);
	
// }

int check_heredoc_quotes(char *delimiter)
{
	if (ft_strchr(delimiter, 34) || ft_strchr(delimiter, 39))
		return (1);
	return (0);	
}

void read_line_heredoc(char *delimiter, char **env)
{
	char *heredoc_input;
	int heredoc_pipe[2];
	char **cmd = ft_split("grep hello", ' ');
	pipe(heredoc_pipe);

	while(1)
	{
		heredoc_input = readline("heredoc> ");
		if (ft_strncmp(delimiter, heredoc_input, ft_strlen(delimiter)) == 0
			&& ft_strlen(delimiter) == ft_strlen(heredoc_input))
			break;
		else
		{
			write(heredoc_pipe[1], heredoc_input, ft_strlen(heredoc_input));
			write(heredoc_pipe[1], "\n", 1);
		}
	}
	dup2(heredoc_pipe[0], STDIN_FILENO);
	close(heredoc_pipe[0]);
	close(heredoc_pipe[1]);
	execve("/usr/bin/grep", cmd, env);
}

int main(int ac, char *av[], char **env)
{
	read_line_heredoc("yassine", env);
	return 0;
}
