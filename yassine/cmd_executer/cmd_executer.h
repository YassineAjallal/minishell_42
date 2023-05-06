/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/30 14:32:57 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
#define TOOLS_H

#include "../structs.h"
#include "../built_in_command/built_in_command.h"

char *cmd_path(char *cmd, char **env);
char *search_command(char *path_var, char *cmd);
int check_path_var(char **env);
int cmd_validation(t_command *cmd);

int ft_strcmp(char *s1, char *s2);

/* file_checker.c */
void	ft_checkf(char *file, int ex);
void	ft_checkw(char *file, int ex);
void	ft_checkr(char *file, int ex);
void	ft_checkx(char *cmd, int ex);
void	ft_perror(int fd, char *s, char *str);

void stdin_redirect(t_command *cmd);
void stdout_redirect(t_command *cmd);
void append_redirect(t_command *cmd);
void exec_built_in(t_command *cmd);
void cmd_exec(t_command *cmd);
#endif