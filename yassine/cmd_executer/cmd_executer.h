/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/23 12:20:54 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
#define TOOLS_H

#include "../structs.h"
#include "../built_in_command/built_in_command.h"

char *cmd_path(t_command *cmd);
char *search_command(char *path_var, char *cmd);
int check_path_var(char **env);
int cmd_validation(t_command *cmd);

int ft_strcmp(char *s1, char *s2);

/* file_checker.c */
int	ft_checkf(char *file);
int	ft_checkw(char *file);
int	ft_checkr(char *file);
int	ft_checkx(char *cmd);

int stdin_redirect(t_command *cmd);
int stdout_redirect(t_command *cmd);
int append_redirect(t_command *cmd);
int exec_built_in(t_command *cmd);
void cmd_exec(t_command *cmd);

void search_built_in(t_command *cmd);

int redirect_in(t_file *infile, t_global_info *g_info);
int redirect_herdoc(t_command *cmd);
int redirect_out(t_file *outfile, int *stdout_fd, t_global_info *g_info);

char *quote_trim(char *str, char c);
int search_heredoc(t_file **file, int i);
#endif