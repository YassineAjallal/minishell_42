/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:23:21 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/25 17:08:53 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "../structs.h"
# include "../cmd_executer/cmd_executer.h"

/*-----pipe_tool.c-----*/
int		init_pipe(int nb_pipe, int (*pipes)[2]);
void	close_pipes(int (*pipes)[2], int nb_pipe);

/*-----pipes.c-----*/
void	one_built_in(t_command *cmd, t_global_info *g_info);
int		*cmds_run(int (*pipe_arr)[2], t_command **cmds, \
t_global_info *g_info, int *pids);
int		pipes(t_command **cmds, t_global_info *g_info);

/*----- process_config.c-----*/
void	child_config(t_command *cmd, int dup_stdin, \
int dup_stdout, int (*pipes)[2]);
void	parent_config(t_command *cmd, int pid);
void	wait_config(t_global_info *g_info, int pids[]);
int		fork_config(t_command *cmd, int dup_stdin, \
int dup_stdout, int (*pipe_arr)[2]);
#endif