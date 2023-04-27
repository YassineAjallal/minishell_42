/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:13:03 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/27 18:58:14 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

/* redirect input */
void stdin_redirect(t_command *cmd)
{
	int stdin_fd;
	if (cmd->redirect_in == true)
	{
		ft_checkf(cmd->infile, 1);
		ft_checkr(cmd->infile, 1);
		stdin_fd = open(cmd->infile, O_RDONLY);
		if (stdin_fd < 0)
		{
			ft_perror(2, "minishell: %s: No such file or directory\n", cmd->infile);
			exit(EXIT_FAILURE);
		}
		if (dup2(stdin_fd, STDIN_FILENO) < 0)
		{
			ft_perror(2, "redirect error", cmd->infile);
			exit(EXIT_FAILURE);
		}
		close(stdin_fd);
	}
}

/* redirect output */
void stdout_redirect(t_command *cmd)
{
	int stdout_fd;
	if (cmd->redirect_in == true)
	{
		stdout_fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (stdout_fd < 0)
		{
			ft_perror(2, "minishell : %s: opening error", cmd->outfile);
			exit(EXIT_FAILURE);

		}
		if (dup2(stdout_fd, STDOUT_FILENO) < 0)
		{
			ft_perror(2, "redirect error", cmd->outfile);
			exit(EXIT_FAILURE);

		}
		close(stdout_fd);
	}
}

/* redirect output in append mode */
void append_redirect(t_command *cmd)
{
	int append_fd;
	if (cmd->redirect_in == true)
	{
		append_fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (append_fd < 0)
		{
			ft_perror(2, "minishell : %s: opening error", cmd->outfile);
			exit(EXIT_FAILURE);
		}
		if (dup2(append_fd, STDOUT_FILENO) < 0)
		{
			ft_perror(2, "redirect error", cmd->outfile);
			exit(EXIT_FAILURE);
		}
	}
}
// void herdoc_mode(t_command *cmd)
// {

// 	char *heredoc_input;
// 	char *cmd_path;
// 	int heredoc_pipe[2];
	
// 	if (cmd->herdoc == true)
// 	{		
// 		if (pipe(heredoc_pipe) < 0)
// 		{
// 			ft_perror(2, "pipe error", cmd->outfile);
// 			exit(EXIT_FAILURE);
// 		}
// 		while(1)
// 		{
// 			heredoc_input = readline("heredoc> ");
// 			if (ft_strncmp(cmd->delemiter, heredoc_input, ft_strlen(cmd->delemiter)) == 0
// 				&& ft_strlen(cmd->delemiter) == ft_strlen(heredoc_input))
// 				break;
// 			else
// 			{
// 				write(heredoc_pipe[1], heredoc_input, ft_strlen(heredoc_input));
// 				write(heredoc_pipe[1], "\n", 1);
// 			}
// 		}
// 		dup2(heredoc_pipe[0], STDIN_FILENO);
// 		close(heredoc_pipe[0]);
// 		close(heredoc_pipe[1]);
// 	}
// }

void cmd_exec(t_command *cmd)
{
	stdin_redirect(cmd);
	stdout_redirect(cmd);
	append_redirect(cmd);
	// herdoc_mode(cmd);
	if (cmd->built_in == false)
	{		
		if(cmd_validation(cmd))
			execve(cmd->command_path, cmd->cmd_parameter, cmd->g_info->env_array);
	}
}
int main(int ac, char **av, char **env)
{
	t_global_info *g_info;
	t_command *cmd;
	cmd = malloc(sizeof(t_command));
	g_info = malloc(sizeof(t_global_info));
	
	g_info->environ = dup_env(env);
	g_info->export_env = dup_env(env);
	g_info->env_array = convert_env_array(g_info->environ);
	cmd->g_info = g_info;
	cmd->cmd = ft_strdup("ls");
	cmd->command_path = cmd_path(cmd->cmd, cmd->g_info->env_array);
	cmd->cmd_parameter = ft_split("ls", ' ');
	/* redirect */
	cmd->built_in = false;
	cmd->redirect_in = false;
	cmd->redirect_append = false;
	cmd->redirect_out = false;
	cmd->herdoc = false;
	cmd_exec(cmd);
}