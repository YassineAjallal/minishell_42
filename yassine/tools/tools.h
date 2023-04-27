/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:42:02 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/27 18:53:44 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
#define TOOLS_H

#include "../minishell.h"
#include "../built_in_command/built_in_command.h"
#include "stdarg.h"

char *cmd_path(char *cmd, char **env);
char *search_command(char *path_var, char *cmd);
int check_path_var(char **env);
int cmd_validation(t_command *cmd);

/* file_checker.c */
void	ft_checkf(char *file, int ex);
void	ft_checkw(char *file, int ex);
void	ft_checkr(char *file, int ex);
void	ft_checkx(char *cmd, int ex);
void	ft_perror(int fd, char *s, char *str);
#endif