/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/30 11:48:01 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXECUTER_H
# define CMD_EXECUTER_H

# include "../structs.h"
# include "../built_in_command/built_in_command.h"
# include "../expander/expander.h"

/*-----cmd_exec.c-----*/
int		stdin_redirect(t_command *cmd);
int		stdout_redirect(t_command *cmd);
void	search_built_in(t_command *cmd);
void	cmd_exec(t_command *cmd, t_global_info *g_info);

/*-----exec_built_in.c-----*/
int		exec_built_in_p1(t_command *cmd);
void	exec_built_in_p2(t_command *cmd, t_global_info *g_info);
int		exec_built_in(t_command *cmd, t_global_info *g_info);

/*-----cmd_tools.c-----*/
int		check_path_var(char **env);
char	*search_command(char *path_var, char *cmd);
char	*cmd_path(t_command *cmd);
int		cmd_validation(t_command *cmd);

/*-----file_checker.c-----*/
int		ft_checkf(char *file);
int		ft_checkw(char *file);
int		ft_checkr(char *file);
int		ft_checkx(char *file);

/*-----redirectionc.c-----*/
int		redirect_in(t_file *infile, t_global_info *g_info);
int		redirect_out(t_file *outfile, int *stdout_fd, t_global_info *g_info);
void	h_readline(t_file *infile, t_global_info *g_info, int heredoc_pipe[2]);
int		herdoc_input(t_file *infile, int heredoc_pipe[2], int herdoc_stdout);
int		redirect_herdoc(t_command *cmd);

/*-----tools.c-----*/
char	*quote_trim(char *str, char c);
int		search_heredoc(t_file **file, int i);
void	handler_herdoc(int signal);
void	herdoc_process(t_file *infile, int is_expanded, \
int heredoc_pipe[2], t_global_info *g_info);
#endif