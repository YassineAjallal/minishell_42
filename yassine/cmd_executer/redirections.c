/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:08:16 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/27 11:20:44 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_executer.h"

int	redirect_in(t_file *infile, t_global_info *g_info)
{
	int	stdin_fd;

	if (infile->mode == true)
	{
		infile->file = ambiguous_redirect(infile->file, g_info);
		if (!infile->file)
			return (0);
		if (!ft_checkf(infile->file) || !ft_checkr(infile->file))
			return (0);
		stdin_fd = open(infile->file, O_RDONLY);
		if (stdin_fd < 0)
		{
			ft_putstr_fd("minishell: No such file or directory\n", 2);
			return (0);
		}
		if (dup2(stdin_fd, STDIN_FILENO) < 0)
		{
			ft_putstr_fd("minishell: redirect error\n", 2);
			return (0);
		}
		close(stdin_fd);
	}
	return (1);
}

int	redirect_out(t_file *outfile, int *stdout_fd, t_global_info *g_info)
{
	outfile->file = ambiguous_redirect(outfile->file, g_info);
	if (!outfile->file)
		return (0);
	if (outfile->mode == true)
		*stdout_fd = open(outfile->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		*stdout_fd = open(outfile->file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (!ft_checkf(outfile->file))
		return (0);
	else if (!ft_checkw(outfile->file))
		return (0);
	if (stdout_fd < 0)
	{
		ft_putstr_fd("minishell: open error\n", 2);
		return (0);
	}
	return (1);
}

void	h_readline(t_file *infile, t_global_info *g_info, int heredoc_pipe[2])
{
	char	*heredoc_input;
	int		is_expanded;

	is_expanded = 0;
	if (!ft_strchr(infile->file, '\'') && !ft_strchr(infile->file, '\"'))
		is_expanded = 1;
	infile->file = quote_trim(infile->file, '\"');
	infile->file = quote_trim(infile->file, '\'');
	while (1)
	{
		heredoc_input = readline("> ");
		if (!heredoc_input)
			return ;
		else if (!ft_strcmp(infile->file, heredoc_input))
			return ;
		else
		{
			if (is_expanded == 1)
				heredoc_input = expand_var(heredoc_input, g_info);
			write(heredoc_pipe[1], heredoc_input, ft_strlen(heredoc_input));
			write(heredoc_pipe[1], "\n", 1);
		}
	}
	return ;
}

int	herdoc_input(t_file *infile, int heredoc_pipe[2], int herdoc_stdout)
{
	if (!infile)
	{
		if (dup2(heredoc_pipe[0], STDIN_FILENO) < 0)
		{
			ft_putstr_fd("minishell: redirect error\n", 2);
			return (0);
		}
	}
	close(heredoc_pipe[0]);
	close(heredoc_pipe[1]);
	if (herdoc_stdout > 1)
	{
		if (dup2(herdoc_stdout, STDOUT_FILENO) < 0)
		{
			ft_putstr_fd("minishell: redirect error\n", 2);
			return (0);
		}
		close(herdoc_stdout);
	}
	return (1);
}

int	redirect_herdoc(t_command *cmd)
{
	int	heredoc_pipe[2];
	int	i;

	i = 0;
	while (cmd->infile[i])
	{
		if (cmd->infile[i]->mode == false)
		{
			if (pipe(heredoc_pipe) < 0)
			{
				ft_putstr_fd("minishell: pipe error\n", 2);
				if (!cmd->infile[i + 1])
					return (0);
			}
			h_readline(cmd->infile[i], cmd->g_info, heredoc_pipe);
			if (!herdoc_input(cmd->infile[i + 1], \
			heredoc_pipe, cmd->herdoc_stdout))
				return (0);
		}
		i++;
	}
	return (1);
}
