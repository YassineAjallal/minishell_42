/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yajallal <yajallal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 21:43:56 by yajallal          #+#    #+#             */
/*   Updated: 2023/04/07 02:12:26 by yajallal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_COMMAND_H
#define BUILT_IN_COMMAND_H

#include "../minishell.h"

typedef struct s_env
{
	char *name;
	char *value;
} t_env;

char *ft_pwd(void);
int ft_strlen2d(char **str);
char *multiple_join(char **path, int length);
void	ft_free2d(char **str);

char **dup_env(char **env);
char **ft_export(char **old_env, char *env_var);
#endif