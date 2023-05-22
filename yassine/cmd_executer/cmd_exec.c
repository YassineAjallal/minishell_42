/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:13:03 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/22 17:00:41 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_executer.h"

/* redirect input */
char *quote_trim(char *str, char c)
{
	int i;
	char **split_quote;
	char *string_trim;

	i = 0;
	string_trim = malloc(sizeof(char));
	string_trim[0] = 0;
	if (!str)
		return (NULL);
	split_quote = ft_split(str, c);
	while(split_quote[i])
	{
		string_trim = ft_strjoin(string_trim, split_quote[i]);
		i++;
	}
	return (string_trim);
}

int stdin_redirect(t_command *cmd)
{
	int i;
	int stdin_fd;
	char *heredoc_input;
	int heredoc_pipe[2];
	int is_expanded;

	is_expanded = 0;
	if (cmd->redirect_in == true)
	{
		i = 0;
		while(cmd->infile[i])
		{
			if (cmd->infile[i]->mode == true)
			{
				cmd->infile[i]->file = ambiguous_redirect(cmd->infile[i]->file, cmd->g_info);
				if(!cmd->infile[i]->file)
					return (0);
				if (!ft_checkf(cmd->infile[i]->file))
				{
					cmd->g_info->exit_code = 1;
					return (0);
				}
				if (!ft_checkr(cmd->infile[i]->file))
				{
					cmd->g_info->exit_code = 1;
					return (0);
				}
				stdin_fd = open(cmd->infile[i]->file, O_RDONLY);
				if (stdin_fd < 0)
				{
					printf("here\n");
					ft_putstr_fd("minishell: No such file or directory\n", 2);
					cmd->g_info->exit_code = 1;
					return (0);
				}
				if (dup2(stdin_fd, STDIN_FILENO) < 0)
				{
					ft_putstr_fd("minishell: redirect error\n", 2);
					cmd->g_info->exit_code = 1;
					return (0);
				}
				close(stdin_fd);
			}
			else if (cmd->infile[i]->mode == false)
			{
				if (!ft_strchr(cmd->infile[i]->file, '\'') && !ft_strchr(cmd->infile[i]->file, '\"'))
					is_expanded = 1;
				cmd->infile[i]->file = quote_trim(cmd->infile[i]->file, '\"');
				cmd->infile[i]->file = quote_trim(cmd->infile[i]->file, '\'');
				if (pipe(heredoc_pipe) < 0)
				{
					ft_putstr_fd("minishell: pipe error\n", 2);
					cmd->g_info->exit_code = 1;
					return (0);
				}
				while(1)
				{
					heredoc_input = readline("> ");
					if (!heredoc_input)
					{
						cmd->g_info->exit_code = 0;
						break;
					}
					else if (!ft_strcmp(cmd->infile[i]->file, heredoc_input))
					{
						cmd->g_info->exit_code = 0;
						break;
					}
					else
					{
						if (is_expanded == 1)
							heredoc_input = expand_var(heredoc_input, cmd->g_info);
						write(heredoc_pipe[1], heredoc_input, ft_strlen(heredoc_input));
						write(heredoc_pipe[1], "\n", 1);
					}
				}
				if (!cmd->infile[i + 1])
				{
					if(dup2(heredoc_pipe[0], STDIN_FILENO) < 0)
					{
						ft_putstr_fd("minishell: redirect error\n", 2);
						cmd->g_info->exit_code = 1;
						return (0);
					}
				}
				close(heredoc_pipe[0]);
				close(heredoc_pipe[1]);
				if (cmd->herdoc_stdout > 1)
				{
					if(dup2(cmd->herdoc_stdout, STDOUT_FILENO) < 0)
					{
						ft_putstr_fd("minishell: redirect error\n", 2);
						cmd->g_info->exit_code = 1;
						return (0);
					}
					close(cmd->herdoc_stdout);
				}
			}
			i++;
		}
	}
	return (1);
}

// char **convert_out_2d(t_outfile **outfile)
// {
// 	int len;
// 	char **outfiles;
// 	int i;

// 	i = 0;
// 	len = 0;
// 	while(outfile[i]->file)
// 	{
// 		len++;
// 		i++;
// 	}
// 	outfiles = malloc(sizeof(char *) * (len + 1));
// 	if (!outfiles)
// 		return (NULL);
// 	i = 0;
// 	while(outfile[i]->file)
// 	{
// 		outfiles[i] = ft_strdup(outfile[i]->file);
// 		i++;
// 	}
// 	outfiles[i] = NULL;
// 	return (outfiles);
// }
/* redirect output */
int stdout_redirect(t_command *cmd)
{
	int stdout_fd;
	int i;
	
	if (cmd->redirect_out == true)
	{
		i = 0;
		while (cmd->outfile[i])
		{
			cmd->outfile[i]->file = ambiguous_redirect(cmd->outfile[i]->file, cmd->g_info);
			if (!cmd->outfile[i]->file)
				return (0);
			if (cmd->outfile[i]->mode == true)
				stdout_fd = open(cmd->outfile[i]->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			else
				stdout_fd = open(cmd->outfile[i]->file, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (!ft_checkf(cmd->outfile[i]->file))
			{
				cmd->g_info->exit_code = 1;
				return (0);
			}
			else if (!ft_checkw(cmd->outfile[i]->file))
			{
				cmd->g_info->exit_code = 1;
				return (0);
			}
			
			if (stdout_fd < 0)
			{
				ft_putstr_fd("minishell: open error\n", 2);
				cmd->g_info->exit_code = 1;
				return (0);
			}	
			i++;
		}
		if (dup2(stdout_fd, STDOUT_FILENO) < 0)
		{
			ft_putstr_fd("minishell: redirect error\n", 2);
			cmd->g_info->exit_code = 1;
			return (0);

		}
	}
	return (1);
}

// int herdoc_mode(t_command *cmd)
// {
// 	char *heredoc_input;
// 	int heredoc_pipe[2];
// 	int is_expanded;
// 	int i;

// 	if (cmd->herdoc == true)
// 	{	
// 		i = 0;
// 		is_expanded = 0;
// 		while(cmd->delemiter[i])
// 		{
// 			if (!ft_strchr("\"\'", cmd->delemiter[i][0]))
// 				is_expanded = 1;
// 			cmd->delemiter[i] = ft_strtrim(cmd->delemiter[i], "\'\"");
// 			if (pipe(heredoc_pipe) < 0)
// 			{
// 				ft_putstr_fd("minishell: pipe error\n", 2);
// 				cmd->g_info->exit_code = 1;
// 				return (0);
// 			}
// 			while(1)
// 			{
// 				heredoc_input = readline("> ");
// 				if (!heredoc_input)
// 				{
// 					cmd->g_info->exit_code = 0;
// 					break;
// 				}
// 				else if (!ft_strcmp(cmd->delemiter[i], heredoc_input))
// 				{
// 					cmd->g_info->exit_code = 0;
// 					break;
// 				}
// 				else
// 				{
// 					if (is_expanded == 1)
// 						heredoc_input = expand_var(heredoc_input, cmd->g_info);
// 					write(heredoc_pipe[1], heredoc_input, ft_strlen(heredoc_input));
// 					write(heredoc_pipe[1], "\n", 1);
// 				}
// 			}
// 			if (!cmd->delemiter[i + 1])
// 			{
// 				if(dup2(heredoc_pipe[0], STDIN_FILENO) < 0)
// 				{
// 					ft_putstr_fd("minishell: redirect error\n", 2);
// 					cmd->g_info->exit_code = 1;
// 					return (0);
// 				}
// 			}
// 			close(heredoc_pipe[0]);
// 			close(heredoc_pipe[1]);
// 			i++;
// 		}
// 		if (cmd->herdoc_stdout > 1)
// 		{
// 			if(dup2(cmd->herdoc_stdout, STDOUT_FILENO) < 0)
// 			{
// 				ft_putstr_fd("minishell: redirect error\n", 2);
// 				cmd->g_info->exit_code = 1;
// 				return (0);
// 			}
// 			close(cmd->herdoc_stdout);
// 		}
// 	}
// 	return (1);
// }
void search_built_in(t_command *cmd)
{
	char **all_built_in;
	int i;

	i = 0;
	if (cmd->cmd)
	{
		all_built_in = ft_split("echo cd pwd export unset env exit", ' ');
		while (all_built_in[i])
		{
			if (!cmd->cmd)
			{
				cmd->built_in = false;
				cmd->g_info->exit_code = 0;
			}
			if (!ft_strcmp(cmd->cmd, all_built_in[i]))
			{
				cmd->built_in = true;
				return;
			}
			else
				cmd->built_in = false;
			i++;
		}
	}
	
}
int exec_built_in(t_command *cmd)
{
	if(!stdin_redirect(cmd))
		return (0);
	if(!stdout_redirect(cmd))
		return (0);
	// if(!herdoc_mode(cmd))
	// 	return (0);
	if(!ft_strcmp(cmd->cmd, "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd->cmd, "env"))
		ft_env(cmd);
	else if (!ft_strcmp(cmd->cmd, "cd"))
	{
		if (!ft_cd(cmd))
			return (0);
	}
	else if (!ft_strcmp(cmd->cmd , "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->cmd , "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(cmd->cmd , "export"))
	{
		if (ft_strlen2d(cmd->cmd_parameter) == 1)
			export_no_param(cmd);
		else
			ft_export(cmd);
	}
	else if (!ft_strcmp(cmd->cmd, "exit"))
	{
		if (ft_exit(cmd))
			exit (cmd->g_info->exit_code);
	}
	return (1);
}
void cmd_exec(t_command *cmd)
{
	search_built_in(cmd);
	if (cmd->built_in == false)
	{
		if(!stdin_redirect(cmd))
			exit(cmd->g_info->exit_code);
		if(!stdout_redirect(cmd))
			exit(cmd->g_info->exit_code);
		// if(!herdoc_mode(cmd))
		// 	exit(cmd->g_info->exit_code);
		if(cmd_validation(cmd))
			execve(cmd->command_path, cmd->cmd_parameter, cmd->g_info->env_array);
		else
			exit(cmd->g_info->exit_code);
	}
	else
	{
		if (!exec_built_in(cmd))
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
}