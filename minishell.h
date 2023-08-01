/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:53:09 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/30 16:00:20 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./cmd_executer/cmd_executer.h"
# include "./built_in_command/built_in_command.h"
# include "./expander/expander.h"
# include "./pars/pars.h"
# include  "./pipes/pipes.h"
# include "structs.h"

/*-----minishell.c-----*/
void			sigint_signal(int signal);
void			sigquit_signal(int signal);

/*-----minishell_tools.c-----*/
t_global_info	*init_g_info(char **env);
void			run_command(char *input, t_global_info *g_info, \
t_command **cmd);
void			minishell_readline(t_global_info *g_info, \
t_command **cmd);
#endif