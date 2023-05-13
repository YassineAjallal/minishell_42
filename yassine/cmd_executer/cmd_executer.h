/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_executer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/05/13 11:51:25 by yajallal         ###   ########.fr       */
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
#endif